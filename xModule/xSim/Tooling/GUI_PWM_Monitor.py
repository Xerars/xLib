#!/usr/bin/env python3

# [模組]
import sys
import re
import numpy as np

# QT
from PyQt6.QtWidgets import QApplication
from PyQt6.QtWidgets import QMainWindow
from PyQt6.QtWidgets import QWidget
from PyQt6.QtWidgets import QVBoxLayout
from PyQt6.QtWidgets import QFileDialog
from PyQt6.QtWidgets import QMessageBox

from PyQt6.QtGui    import QAction
from PyQt6.QtGui    import QActionGroup

# Matplotlib
import matplotlib
from matplotlib.backends.backend_qtagg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qtagg import NavigationToolbar2QT as NavigationToolbar
from matplotlib.figure import (Figure)
matplotlib.use('QtAgg')        # 指定使用 PyQt 渲染後端

# [變數]
CONFIG_WINDOW_TITLE = "GUI Simulate PWM Waveform Monitor"
CONFIG_STYLE_FILE   = "Style.qss"


# [Class]
class GUI_PWM_Window(QMainWindow):
  # 建構子
  def __init__(self):
    super().__init__()
    self.setWindowTitle(CONFIG_WINDOW_TITLE)

    Win_W,Win_H = self.GUI_GetScreenSize()
    Win_W = 1500
    Win_H = 760
    self.resize(Win_W,Win_H)
    
    self.Current_Data = None        # 記錄目前載入的 PWM 資料
    self.View_Mode    = "Single"    # 預設檢視模式為單圖
    
    self.GUI_Init()

  # Function: GUI_Init
  # Descript: 初始化主視窗與元件
  def GUI_Init(self):
    self.GUI_MenuBar_Create()
    self.GUI_StatusBar_Create()

    # 2. 建立中央主元件與 Layout
    Central_Widget = QWidget()
    self.setCentralWidget(Central_Widget)
    Main_Layout = QVBoxLayout(Central_Widget)
    Main_Layout.setContentsMargins(10,10,10,10)

    self.Canvas = self.GUI_Plot_Create()
    Main_Layout.addWidget(self.Canvas)

    # 建立並加入 Matplotlib 互動工具列 (提供放大、平移、復原功能)
    self.Toolbar = NavigationToolbar(self.Canvas,self)
    Main_Layout.addWidget(self.Toolbar)


  # Function: GUI_MenuBar_Create
  # Descript: 建立頂部選單列與動作
  def GUI_MenuBar_Create(self):
    Menu        = self.menuBar()                # 建立 MenuBar
    Menu_File   = Menu.addMenu("檔案(&F)")
    Menu_View   = Menu.addMenu("檢視(&V)")
    Menu_Info   = Menu.addMenu("資訊(&I)")

    # 載入
    Act_Load = QAction("載入",self)
    Act_Load.setShortcut("Ctrl+O")
    Act_Load.triggered.connect(self.Menu_File_Load_Event)
    Menu_File.addAction(Act_Load)

    # 儲存
    Act_Save = QAction("儲存",self)
    Act_Save.setShortcut("Ctrl+S")
    Act_Save.triggered.connect(self.Menu_File_Save_Event)
    Menu_File.addAction(Act_Save)
    Menu_File.addSeparator()                    # 分隔線

    # 離開
    Act_Exit = QAction("離開",self)
    Act_Exit.setShortcut("Ctrl+Q")
    Act_Exit.triggered.connect(self.Menu_File_Exit_Event)
    Menu_File.addAction(Act_Exit)

    # 說明
    Act_Help = QAction("說明",self)
    Act_Help.setShortcut("Ctrl+I")
    Act_Help.triggered.connect(self.Menu_Info_Help_Event)
    Menu_Info.addAction(Act_Help)
  
    # 關於
    Act_About = QAction("關於",self)
    Act_About.setShortcut("Ctrl+B")
    Act_About.triggered.connect(self.Menu_Info_About_Event)
    Menu_Info.addAction(Act_About)

    # 檢視群組 (單選互斥)
    self.View_Group = QActionGroup(self)
    self.View_Group.setExclusive(True)        # 設定為互斥單選

    # 子項目 1：單圖顯示 (預設)
    self.Act_View_Single = QAction("單圖顯示",self,checkable=True)
    self.Act_View_Single.setChecked(True)     # 預設勾選這個
    self.Act_View_Single.triggered.connect(lambda: self.Menu_View_Mode_Event("Single"))
    self.View_Group.addAction(self.Act_View_Single)
    Menu_View.addAction(self.Act_View_Single)
    Menu_View.addSeparator()                  # 分隔線

    # 子項目 2：多圖顯示 
    self.Act_View_Multiple = QAction("多圖顯示",self,checkable=True)
    self.Act_View_Multiple.triggered.connect(lambda: self.Menu_View_Mode_Event("Multiple"))
    self.View_Group.addAction(self.Act_View_Multiple)
    Menu_View.addAction(self.Act_View_Multiple)


  # Function: GUI_StatusBar_Create
  # Descript: 建立底部狀態列
  def GUI_StatusBar_Create(self):
    self.statusBar().showMessage("")      # 建立空白的狀態列


  # Function: GUI_Plot_Create
  # Descript: 建立圖表畫布與預設格式 (仿示波器 High/Low 波形)
  def GUI_Plot_Create(self):
    Fig = Figure(figsize=(5,4),dpi=100)
    self.Ax = Fig.add_subplot(111)
    
    self.Ax.set_title("PWM Waveform Monitor",fontsize=12)
    self.Ax.set_xlabel("Time (s)",fontsize=10)
    self.Ax.set_ylabel("Level",fontsize=10)

    self.Ax.set_yticks([0,1])
    self.Ax.set_yticklabels(["Low(0)","High(1)"])
    self.Ax.set_ylim(-0.1,1.1)
    self.Ax.grid(True,linestyle="--",alpha=0.6)
    
    Canvas = FigureCanvas(Fig)
    return Canvas


  # Function: GUI_Plot_Update
  # Descript: 更新並繪製 PWM 實際方波波形
  def GUI_Plot_Update(self,Data,Mode="Single"):
    All_Channels = []
    for Index,Info in sorted(Data["PWM"].items()):
      All_Channels.append(("PWM",Index,Info))

    TOT_Channel = len(All_Channels)
    
    if TOT_Channel == 0:
      self.Canvas.figure.clear()
      self.Ax = self.Canvas.figure.add_subplot(111)
      self.Ax.set_title("PWM Monitor - No Data",fontsize=12)
      self.Ax.set_yticks([0])
      self.Ax.set_yticklabels(["No Data"])
      self.Canvas.draw()
      return

    self.Canvas.figure.clear()

    if Mode == "Single":
      nPlots = 1
      Rows,Cols = 1,1
    else:
      if TOT_Channel == 1:
        nPlots = 1
        Rows,Cols = 1,1
      elif TOT_Channel == 2:
        nPlots = 2
        Rows,Cols = 2,1  # 兩個圖上下排列
      else:
        nPlots = 4
        Rows,Cols = 2,2  # 四個圖 2x2 排列

    Fig_Axes = self.Canvas.figure.subplots(nrows=Rows,ncols=Cols,sharex=True)
    
    if isinstance(Fig_Axes,matplotlib.axes.Axes):
      axes = [Fig_Axes]
    else:
      axes = Fig_Axes.flatten()

    Channel_Map = {i: [] for i in range(nPlots)}
    if Mode == "Single":
      Channel_Map[0] = [(idx,ch) for idx,ch in enumerate(All_Channels)]
    else:
      for idx,ch in enumerate(All_Channels):
        group_idx = idx % nPlots
        Channel_Map[group_idx].append((idx,ch))

    Colors = matplotlib.colormaps['tab10'].colors

    for i,Ax in enumerate(axes):
      if i < nPlots and i in Channel_Map and len(Channel_Map[i]) > 0:
        for global_idx,(IO_Type,Index,Info) in Channel_Map[i]:
          Times  = Info["Time"]
          Values = Info["Value"]
          line_color = Colors[global_idx % len(Colors)]
          
          # 繪製方波波形 (使用 step 或直接 plot)
          Ax.step(Times,Values,where='post',linewidth=1.5,color=line_color,label=f"PWM-{Index} <{Info['Name']}>")

        Ax.set_yticks([0,1])
        Ax.set_yticklabels(["Low (0)","High (1)"])
        Ax.set_ylim(-0.1,1.1)
        Ax.grid(True,linestyle="--",alpha=0.6)
        Ax.legend(loc="upper right",fontsize=7,ncol=2)

        if Mode == "Single":
          Ax.set_title("PWM Monitor - Waveform View (Single)",fontsize=12)
          Ax.set_xlabel("Time (s)",fontsize=10)
          Ax.set_ylabel("Level",fontsize=10)
        else:
          Ax.set_title(f"PWM Group {i+1} (Channels: {len(Channel_Map[i])})",fontsize=10)
          Ax.set_xlabel("Time (s)",fontsize=9)
          Ax.set_ylabel("Level",fontsize=9)
      else:
        Ax.axis('off')

    self.Canvas.figure.tight_layout()
    self.Canvas.draw()


  # Function: GUI_GetScreenSize
  # Descript: 取得目前螢幕解析度大小
  def GUI_GetScreenSize(self):
    Screen   = QApplication.primaryScreen()
    Geometry = Screen.geometry()
    print(f"Windows Width: {Geometry.width()} ,Windows Heigh: {Geometry.height()}")
    return Geometry.width(),Geometry.height()


  # Function: Menu_File_Load_Event
  # Descript: 處理檔案載入事件
  def Menu_File_Load_Event(self):
    print("[Trig]: Menu File Load Event")

    File_Path,File_Filter = QFileDialog.getOpenFileName(self,"選擇 PWM LOG 檔案",
                                                        ".","Log Files (*.log *.txt);;All Files (*)")
    if File_Path:
      print(f"[Success]: Select File: {File_Path}")
      Data = Parse_PWM_Data(File_Path)

      if Data:
        self.Current_Data = Data
        self.GUI_Plot_Update(Data,self.View_Mode)
        self.statusBar().showMessage(f"已載入 PWM 檔案: {File_Path}",2000)
      else:
        self.statusBar().showMessage(f"解析失敗: {File_Path}",2000)
    else:
      print("[Info]: Cancel File Select")


  # Function: Menu_File_Save_Event
  # Descript: 處理圖表檔案儲存事件
  def Menu_File_Save_Event(self):
    print("[Trig]: Menu File Save Event")
    if not self.Current_Data:
      QMessageBox.warning(self,"警告","目前沒有可儲存的 PWM 圖表資料！請先載入 Log 檔案。")
      return

    File_Path,File_Filter = QFileDialog.getSaveFileName(self,
      "儲存 PWM 圖表",
      ".",
      "PNG Image (*.png);;JPEG Image (*.jpg);;PDF Document (*.pdf);;All Files (*)")

    if File_Path:
      if not any(File_Path.lower().endswith(ext) for ext in ['.png','.jpg','.jpeg','.pdf']):
        if "(*.jpg)" in File_Filter:
          File_Path += ".jpg"
        elif "(*.pdf)" in File_Filter:
          File_Path += ".pdf"
        elif "(*.png)" in File_Filter:
          File_Path += ".png"

      try:
        self.Canvas.figure.savefig(File_Path,dpi=300,bbox_inches='tight')
        self.statusBar().showMessage(f"PWM 圖表已成功儲存: {File_Path}",3000)
      except Exception as e:
        QMessageBox.critical(self,"錯誤",f"儲存檔案失敗！\n錯誤訊息: {e}")
    else:
      print("[Info]: Cancel File Save")


  # Function: Menu_File_Exit_Event
  # Descript: 處理離開應用程式事件
  def Menu_File_Exit_Event(self):
    print("[Trig]: Menu File Exit Event")
    self.close()


  # Function: Menu_Info_Help_Event
  # Descript: 顯示操作說明對話框
  def Menu_Info_Help_Event(self):
    print("[Trig]: Menu Info Help Event")
    QMessageBox.information(self,
      "說明",
      "【GUI Simulate PWM Waveform Monitor 說明】\n\n"
        "1. 點擊[檔案]->[載入]讀取 PWM Log\n"
        "2. 格式: 時間::[PWM-編號]<名稱> 指令(參數)\n"
        "3. 系統將根據 Freq 與 Duty 在各時間段自動生成實際的高低脈衝波形。\n"
        "4. 可使用下方工具列的放大鏡按鈕進行區塊放大，或用移動按鈕平移波形。")


  # Function: Menu_Info_About_Event
  # Descript: 顯示關於本軟體的資訊對話框
  def Menu_Info_About_Event(self):
    print("[Trig]: Menu Info About Event")
    QMessageBox.about(self,
      "關於",
      "GUI Simulate PWM Waveform Monitor\n"
      "版本: 1.1\n"
      "目標: Linux Module xSim Tooling\n"
      "作者: William Hsiao")


  # Function: Menu_View_Mode_Event
  # Descript: 處理檢視模式切換事件 (單圖/多圖)
  def Menu_View_Mode_Event(self,Mode):
    print(f"[Trig]: Switch View Mode -> {Mode}")
    self.View_Mode = Mode
    if self.Current_Data:
      self.GUI_Plot_Update(self.Current_Data,self.View_Mode)


# Function: Load_StyleSheet
# Descript: 載入外部 QSS 樣式表檔案
def Load_StyleSheet(App,FileName):
  try:
    with open(FileName,"r",encoding="utf-8") as File:
      App.setStyleSheet(File.read())
      print(f"[Success]: Load Style Sheet: {FileName}")
  except FileNotFoundError:
    print(f"Can Not Style Sheet File: {FileName}... Use Default")


# Function: Parse_PWM_Data
# Descript: 解析 PWM Log 並根據各區段的 Freq 與 Duty 實際模擬產生連續脈衝方波
def Parse_PWM_Data(File_Path):
  Parse_Data = { "PWM": {} }

  Pattern_Start   = re.compile(r"^\s*(\d+)::\[(PWM)-(\d+)\]<([^>]+)>\s*Start\(Freq:(\d+)Hz,Duty:(\d+)%\)")
  Pattern_SetFreq = re.compile(r"^\s*(\d+)::\[(PWM)-(\d+)\]<([^>]+)>\s*SetFreq:\s*(\d+)Hz")
  Pattern_SetDuty = re.compile(r"^\s*(\d+)::\[(PWM)-(\d+)\]<([^>]+)>\s*SetDuty:\s*(\d+)%")
  Pattern_Stop    = re.compile(r"^\s*(\d+)::\[(PWM)-(\d+)\]<([^>]+)>\s*Stop")

  RawEvts = []

  try:
    with open(File_Path,"r",encoding="utf-8") as f:
      for Line in f:
        Line = Line.strip()
        if not Line:
          continue

        m = Pattern_Start.match(Line)
        if m:
          RawEvts.append((int(m.group(1)),int(m.group(3)),m.group(4),'START',int(m.group(5)),int(m.group(6))))
          continue

        m = Pattern_SetFreq.match(Line)
        if m:
          RawEvts.append((int(m.group(1)),int(m.group(3)),m.group(4),'FREQ',int(m.group(5)),0))
          continue

        m = Pattern_SetDuty.match(Line)
        if m:
          RawEvts.append((int(m.group(1)),int(m.group(3)),m.group(4),'DUTY',0,int(m.group(5))))
          continue

        m = Pattern_Stop.match(Line)
        if m:
          RawEvts.append((int(m.group(1)),int(m.group(3)),m.group(4),'STOP',0,0))
          continue

    # 1. 嚴格依時間排序事件
    RawEvts.sort(key=lambda x: x[0])

    # 2. 將全域事件拆解成「每個通道各自的時間段區間 (Intervals)」
    Ch_Intervals = {}
    Ch_Active_State = {} 

    for Evt in RawEvts:
      TimeMS,Idx,name,Cmd = Evt[0],Evt[1],Evt[2],Evt[3]

      if Idx not in Ch_Active_State:
        Ch_Active_State[Idx] = {"Name": name,"Freq": 0,"Duty": 0,"Running": False,"LastMS": TimeMS}
        Ch_Intervals[Idx] = []

      State = Ch_Active_State[Idx]
      LastMS = State["LastMS"]

      if State["Running"] and TimeMS > LastMS:
        Ch_Intervals[Idx].append({
          "Start": LastMS,
          "End"  : TimeMS,
          "Freq" : State["Freq"],
          "Duty" : State["Duty"],
          "Name" : State["Name"]
        })

      State["Name"] = name
      State["LastMS"] = TimeMS

      if Cmd == 'START':
        State["Freq"] = Evt[4]
        State["Duty"] = Evt[5]
        State["Running"] = True
      elif Cmd == 'FREQ':
        State["Freq"] = Evt[4]
      elif Cmd == 'DUTY':
        State["Duty"] = Evt[5]
      elif Cmd == 'STOP':
        State["Running"] = False
        State["Freq"] = 0
        State["Duty"] = 0

    # 根據每個通道的區段，自動計算並填入高低電位波形點 (Time / Value)
    for Idx,Intervals in Ch_Intervals.items():
      if not Intervals:
        continue
      
      Ch_Name = Intervals[0]["Name"]
      TimeList  = []
      ValueList = []
      TimeList.append(Intervals[0]["Start"] / 1000.0)
      ValueList.append(0)

      for Interval in Intervals:
        Start_Sec = Interval["Start"] / 1000.0
        End_Sec   = Interval["End"] / 1000.0
        Freq      = Interval["Freq"]
        Duty      = Interval["Duty"]

        if Freq <= 0 or Duty <= 0:
          TimeList.append(End_Sec)
          ValueList.append(0)
          continue

        Period = 1.0 / Freq
        HTime  = Period * (Duty / 100.0)
        LTime  = Period * (1.0 - (Duty / 100.0))

        t = Start_Sec
        while t < End_Sec:
          HEnd = min(t + HTime,End_Sec)
          TimeList.extend([t,HEnd])
          ValueList.extend([1,1])
          t = HEnd

          if t >= End_Sec:
            break

          LEnd = min(t + LTime,End_Sec)
          TimeList.extend([t,LEnd])
          ValueList.extend([0,0])
          t = LEnd

        TimeList.append(End_Sec)
        ValueList.append(0)

      Parse_Data["PWM"][Idx] = {
        "Name" : Ch_Name,
        "Time" : TimeList,
        "Value": ValueList
      }

    print(f"[Success]: Parse PWM Waveform Data Success!")
    print(f"  - PWM Channel: {list(Parse_Data['PWM'].keys())}")
    return Parse_Data

  except Exception as e:
    print(f"[Error]: Parse PWM Log Failed!!({e})")
    return None


# 主程序
if __name__ == "__main__":
  App = QApplication(sys.argv)
  Load_StyleSheet(App,CONFIG_STYLE_FILE)
  Win = GUI_PWM_Window()
  Win.show()
  sys.exit(App.exec())