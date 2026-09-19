#!/usr/bin/env python3

# [模組]
import sys
import re

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
from matplotlib.figure import (Figure)
matplotlib.use('QtAgg')        # 指定使用 PyQt 渲染後端

# [變數]
CONFIG_WINDOW_TITLE = "GUI Simulate ADC Monitor"
CONFIG_STYLE_FILE   = "Style.qss"


# [Class]
class GUI_ADC_Window(QMainWindow):
  # 建構子
  def __init__(self):
    super().__init__()
    self.setWindowTitle(CONFIG_WINDOW_TITLE)

    Win_W,Win_H = self.GUI_GetScreenSize()
    Win_W = 1500
    Win_H = 760
    self.resize(Win_W,Win_H)
    
    self.Current_Data = None        # 記錄目前載入的 ADC 資料
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
  # Descript: 建立圖表畫布與預設格式
  def GUI_Plot_Create(self):
    Fig = Figure(figsize=(5,4),dpi=100)
    self.Ax = Fig.add_subplot(111)
    self.Ax.set_title("ADC Monitor - Waveform View",fontsize=12)
    self.Ax.set_xlabel("Time (s)",fontsize=10)
    self.Ax.set_ylabel("ADC Value",fontsize=10)
    self.Ax.grid(True,linestyle="--",alpha=0.6)
    Canvas = FigureCanvas(Fig)
    return Canvas


  # Function: GUI_Plot_Update
  # Descript: 更新並繪製 ADC 趨勢圖 (支援動態多圖與平均分配)
  def GUI_Plot_Update(self,Data,Mode="Single"):
    # 1. 收集所有 ADC 通道的清單
    All_Channels = []
    for Index,Info in sorted(Data["ADC"].items()):
      All_Channels.append(("ADC",Index,Info))

    TOT_Channel = len(All_Channels)
    if TOT_Channel == 0:
      self.Canvas.figure.clear()
      self.Ax = self.Canvas.figure.add_subplot(111)
      self.Ax.set_title("ADC Monitor - No Data",fontsize=12)
      self.Ax.set_ylabel("No Data")
      self.Canvas.draw()
      return

    # 2. 根據模式與通道數動態決定佈局
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

    # 開始繪製每一張子圖 (ADC 使用連續折線圖 plot + 圓點標記)
    for i,Ax in enumerate(axes):
      if i < nPlots and i in Channel_Map and len(Channel_Map[i]) > 0:
        for global_idx,(IO_Type,Index,Info) in Channel_Map[i]:
          Times  = Info["Time"]
          Values = Info["Value"]
          line_color = Colors[global_idx % len(Colors)]
          
          # ADC 使用帶點的折線圖呈現數值趨勢
          Ax.plot(Times,Values,marker='o',markersize=4,linewidth=1.5,color=line_color,label=f"{IO_Type}-{Index}")

        Ax.grid(True,linestyle="--",alpha=0.6)
        Ax.legend(loc="upper right",fontsize=7,ncol=2)

        if Mode == "Single":
          Ax.set_title("ADC Monitor - Waveform View (Single)",fontsize=12)
          Ax.set_xlabel("Time (s)",fontsize=10)
          Ax.set_ylabel("ADC Value",fontsize=10)
        else:
          Ax.set_title(f"ADC Group {i+1} (Channels: {len(Channel_Map[i])})",fontsize=10)
          Ax.set_xlabel("Time (s)",fontsize=9)
          Ax.set_ylabel("ADC Value",fontsize=9)
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

    File_Path,File_Filter = QFileDialog.getOpenFileName(self,"選擇 ADC LOG 檔案",
                                                        ".","Log Files (*.log *.txt);;All Files (*)")
    if File_Path:
      print(f"[Success]: Select File: {File_Path}")
      Data = Parse_ADC_Data(File_Path)

      if Data:
        self.Current_Data = Data
        self.GUI_Plot_Update(Data,self.View_Mode)
        self.statusBar().showMessage(f"已載入 ADC 檔案: {File_Path}",2000)
      else:
        self.statusBar().showMessage(f"解析失敗: {File_Path}",2000)
    else:
      print("[Info]: Cancel File Select")


  # Function: Menu_File_Save_Event
  # Descript: 處理圖表檔案儲存事件
  def Menu_File_Save_Event(self):
    print("[Trig]: Menu File Save Event")
    if not self.Current_Data:
      QMessageBox.warning(self,"警告","目前沒有可儲存的 ADC 圖表資料！請先載入 Log 檔案。")
      return

    File_Path,File_Filter = QFileDialog.getSaveFileName(self,
      "儲存 ADC 圖表",
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
        self.statusBar().showMessage(f"ADC 圖表已成功儲存: {File_Path}",3000)
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
      "【GUI Simulate ADC Monitor 說明】\n\n"
        "1. 點擊[檔案]->[載入]讀取 ADC Log\n"
        "2. 格式: 時間::[ADC-編號]: 數值 (十六進位)\n"
        "   例如: 0::[ADC-0]: 148 (0x94)\n"
        "3. 系統將自動解析 ADC 數值並繪製趨勢圖。")


  # Function: Menu_Info_About_Event
  # Descript: 顯示關於本軟體的資訊對話框
  def Menu_Info_About_Event(self):
    print("[Trig]: Menu Info About Event")
    QMessageBox.about(self,
      "關於",
      "GUI Simulate ADC Monitor\n"
      "版本: 1.0\n"
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


# Function: Parse_ADC_Data
# Descript: 解析 ADC Log 檔案內容
def Parse_ADC_Data(File_Path):
  Parse_Data = { "ADC": {} }

  # ADC 格式正規表達式
  Pattern = re.compile(r"^\s*(\d+)::\[(ADC)-(\d+)\]:\s*(\d+)\s*\(([^)]+)\)")

  try:
    with open(File_Path,"r",encoding="utf-8") as f:
      for Line in f:
        Match = Pattern.match(Line)
        if Match:
          Time_MS  = int(Match.group(1))
          IO_Type  = Match.group(2)
          Index    = int(Match.group(3))
          Value    = int(Match.group(4))   # 擷取十進位數值
          # Hex_Val  = Match.group(5)       # 保留十六進位供未來參考
          Time_Sec = Time_MS / 1000.0

          if Index not in Parse_Data[IO_Type]:
            Parse_Data[IO_Type][Index] = {
              "Time" : [],
              "Value": []}

          Parse_Data[IO_Type][Index]["Time"].append(Time_Sec)
          Parse_Data[IO_Type][Index]["Value"].append(Value)
          
    print(f"[Success]: Parse ADC Log Data Success!!")
    print(f"  - ADC Channel: {list(Parse_Data['ADC'].keys())}")
    return Parse_Data
    
  except Exception as e:
    print(f"[Error]: Parse ADC Log Failed!!({e})")
    return None

# 主程序
if __name__ == "__main__":
  App = QApplication(sys.argv)
  Load_StyleSheet(App,CONFIG_STYLE_FILE)
  Win = GUI_ADC_Window()
  Win.show()
  sys.exit(App.exec())