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
matplotlib.use('QtAgg')         # 指定使用 PyQt 渲染後端

# [變數]
CONFIG_WINDOW_TITLE = "GUI Simulate I2C Monitor"
CONFIG_STYLE_FILE   = "Style.qss"


# [Class]
class GUI_GPIO_Window(QMainWindow):
  # 建構子
  def __init__(self):
    super().__init__()
    self.setWindowTitle(CONFIG_WINDOW_TITLE)

    Win_W,Win_H = self.GUI_GetScreenSize()
    Win_W = 1500
    Win_H = 760
    self.resize(Win_W,Win_H)
    self.Current_Data = None        # 記錄目前載入的資料
    self.View_Mode    = "Single"    # 預設檢視模式為單圖
    self.GUI_Init()

  # Function: GUI_Init
  # Descript: 初始化主視窗與元件
  def GUI_Init(self):
    self.GUI_MenuBar_Create()
    self.GUI_StatusBar_Create()

    # 建立中央主元件與 Layout
    Central_Widget = QWidget()
    self.setCentralWidget(Central_Widget)
    Main_Layout = QVBoxLayout(Central_Widget)
    Main_Layout.setContentsMargins(10,10,10,10)

    self.Canvas = self.GUI_Plot_Create()
    Main_Layout.addWidget(self.Canvas)


  # Function: GUI_MenuBar_Create
  # Descript: 建立頂部選單列與動作
  def GUI_MenuBar_Create(self):
    Menu      = self.menuBar()                  # 建立 MenuBar
    Menu_File = Menu.addMenu("檔案(&F)")
    Menu_View = Menu.addMenu("檢視(&V)")
    Menu_Info = Menu.addMenu("資訊(&I)")

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

    # 檢視群組(單選互斥)
    self.View_Group = QActionGroup(self)
    self.View_Group.setExclusive(True)        # 設定為互斥單選

    # 子項目 1：單圖顯示(預設)
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
    
    self.Ax.set_title("I2C Register Monitor",fontsize=12)
    self.Ax.set_xlabel("Time (ms)",fontsize=10)
    self.Ax.set_ylabel("Register Value (Hex)",fontsize=10)

    YTicks = list(range(0,256,16))
    YTick_Labels = [f"{v:02X}h" for v in YTicks]
    self.Ax.set_yticks(YTicks)
    self.Ax.set_yticklabels(YTick_Labels)
    self.Ax.set_ylim(-15,275)
    
    self.Ax.grid(True,linestyle="--",alpha=0.6)
    Canvas = FigureCanvas(Fig)
    return Canvas


  # Function: GUI_Plot_Update
  # Descript: 根據單圖或多圖模式更新繪製圖表，並支援多通道分色箭頭
  def GUI_Plot_Update(self,Data,Mode="Single"):
    self.Canvas.figure.clear()

    if not Data or "I2C" not in Data or not Data["I2C"]:
      self.Ax = self.Canvas.figure.add_subplot(111)
      self.Ax.set_title("I2C Monitor - No Data",fontsize=12)
      self.Canvas.draw()
      return

    Base_Colors = matplotlib.colormaps['tab10'].colors
    MaxTime = 1000
    for Evts in Data["I2C"].values():
      for Evt in Evts:
        if Evt["Time"] > MaxTime:
          MaxTime = Evt["Time"]

    Device = list(Data["I2C"].keys())
    YTicks = list(range(0,256,16))
    YTick_Labels = [f"{v:02X}h" for v in YTicks]

    # 模式一: 多圖顯示(Multiple)
    if Mode == "Multiple" and len(Device) > 0:
      nDevs = len(Device)
      Fig = self.Canvas.figure
      
      for Idx,Dev_Name in enumerate(Device):
        Ax        = Fig.add_subplot(nDevs,1,Idx + 1)
        BaseColor = Base_Colors[Idx % len(Base_Colors)]
        Evts      = Data["I2C"][Dev_Name]

        Proc_PTS = self.Cal_Non_OverLap_Point(Evts,BaseColor)
        Ax.set_title(f"Device: {Dev_Name}",fontsize=10,loc='left')
        Ax.set_ylabel("Value (Hex)",fontsize=9)
        
        Ax.set_yticks(YTicks)
        Ax.set_yticklabels(YTick_Labels)
        Ax.set_ylim(-15,275)
        Ax.set_xlim(-50,MaxTime * 1.18)
        Ax.grid(True,linestyle="--",alpha=0.6)

        for p in Proc_PTS:
          OT ,OV  = p["Org_Time"] ,p["Org_Val"]
          PT ,PV  = p["Plot_Time"],p["Plot_Val"]
          LBL,CLR = p["Label"]    ,p["Color"]
          
          Ax.scatter([PT],[PV],color=CLR,s=45,zorder=3)
          
          if OT != PT or OV != PV:
            Ax.plot([OT,PT],[OV,PV],color=CLR,linestyle=":",alpha=0.6,linewidth=1)
            
          if p["Prev"] is not None:
            Prev_PT = p["Prev"]
            Ax.annotate("",xy=(PT,PV),xycoords='data',xytext=(Prev_PT["Plot_Time"],Prev_PT["Plot_Val"]),textcoords='data',
              arrowprops=dict(arrowstyle="->",color=CLR,lw=1.3,alpha=0.9,connectionstyle="arc3,rad=0.25"))

          Ax.text(PT + 6,PV,LBL,fontsize=7.5,color=CLR,va='center')
        Ax.plot([],[],marker="o",color=BaseColor,linestyle="None",label=Dev_Name)
        Ax.legend(loc="upper right",fontsize=8)

        if Idx == nDevs - 1:
          Ax.set_xlabel("Time (ms)",fontsize=10)

      Fig.tight_layout()
      self.Canvas.draw()
      return

    # 模式二: 單圖顯示(Single)
    self.Ax = self.Canvas.figure.add_subplot(111)
    Color_Idx = 0

    for Dev_Name,Evts in Data["I2C"].items():
      BaseColor = Base_Colors[Color_Idx % len(Base_Colors)]
      Color_Idx += 1
      Proc_PTS = self.Cal_Non_OverLap_Point(Evts,BaseColor)

      for p in Proc_PTS:
        OT,OV = p["Org_Time"],p["Org_Val"]
        PT,PV = p["Plot_Time"],p["Plot_Val"]
        LBL,CLR = p["Label"],p["Color"]

        self.Ax.scatter([PT],[PV],color=CLR,s=50,zorder=3)

        if OT != PT or OV != PV:
          self.Ax.plot([OT,PT],[OV,PV],color=CLR,linestyle=":",alpha=0.6,linewidth=1)

        if p["Prev"] is not None:
          Prev_PT = p["Prev"]
          self.Ax.annotate("",xy=(PT,PV),xycoords='data',
            xytext=(Prev_PT["Plot_Time"],Prev_PT["Plot_Val"]),textcoords='data',
            arrowprops=dict(arrowstyle="->",color=CLR,lw=1.3,alpha=0.9,connectionstyle="arc3,rad=0.25"))

        self.Ax.text(PT + 6,PV,LBL,fontsize=7.5,color=CLR,va='center')
      self.Ax.plot([],[],marker="o",color=BaseColor,linestyle="None",label=Dev_Name)

    self.Ax.set_title("I2C Register Read/Write Monitor",fontsize=12)
    self.Ax.set_xlabel("Time (ms)",fontsize=10)
    self.Ax.set_ylabel("Register Value (Hex)",fontsize=10)
    self.Ax.set_yticks(YTicks)
    self.Ax.set_yticklabels(YTick_Labels)
    self.Ax.set_ylim(-15,275)
    self.Ax.set_xlim(-50,MaxTime * 1.18)
    self.Ax.grid(True,linestyle="--",alpha=0.6)
    self.Ax.legend(loc="upper right",fontsize=8)
    self.Canvas.figure.tight_layout()
    self.Canvas.draw()


  # Function: Cal_Non_OverLap_Point
  # Descript: 依據時間與暫存器通道進行防重疊，並賦予不同通道獨立的箭頭顏色
  def Cal_Non_OverLap_Point(self,Evts,BaseColor):
    Distinct_Colors = [
      BaseColor,          # 基準色
      (0.85,0.15,0.15),   # 鮮紅色
      (0.10,0.65,0.20),   # 鮮綠色
      (0.55,0.10,0.75),   # 紫色
      (0.05,0.55,0.65),   # 青色
      (0.90,0.45,0.05),   # 橘金色
      (0.40,0.40,0.40)]   # 深灰色
    AllPoint = []
    for Idx,Evt in enumerate(Evts):
      Reg_Match = re.search(r'\[([0-9A-Fa-f]+)h?\]',Evt["Label"])
      Reg_Key = Reg_Match.group(1) if Reg_Match else "00"

      AllPoint.append({
        "index"  : Idx,
        "time"   : Evt["Time"],
        "value"  : Evt["Value"],
        "Reg_Key": Reg_Key,
        "Label"  : Evt["Label"]})

    AllPoint.sort(key=lambda x: (x["time"],x["index"]))
    
    Adj_Point = []
    tGroup_Point = {}

    for PT in AllPoint:
      t = PT["time"]
      if t not in tGroup_Point:
        tGroup_Point[t] = []
      tGroup_Point[t].append(PT)

    for t,PTS in tGroup_Point.items():
      Channel_Map = {}
      for PT in PTS:
        RKey = PT["Reg_Key"]
        if RKey not in Channel_Map:
          Channel_Map[RKey] = []
        Channel_Map[RKey].append(PT)

      channel_idx = 0
      for RKey,Ch_PTS in Channel_Map.items():
        Ch_Color = Distinct_Colors[channel_idx % len(Distinct_Colors)]
        channel_idx += 1

        Prev_PT = None
        for i,PT in enumerate(Ch_PTS):
          v = PT["value"]
          
          Plot_Val = v
          Plot_Time = t
          Step = 14
          Multiplier = i
          
          while any(abs(ap["Plot_Val"] - Plot_Val) < 12 and abs(ap["Plot_Time"] - Plot_Time) < 25 for ap in Adj_Point):
            Plot_Val  = v + (Multiplier + 1) * Step
            Plot_Time = t + (Multiplier * 3)
            Multiplier += 1

          Plot_Val = max(5,min(250,Plot_Val))
          Proc_PT = {
            "Org_Time" : t,
            "Org_Val"  : v,
            "Plot_Time": Plot_Time,
            "Plot_Val" : Plot_Val,
            "Label"    : PT["Label"],
            "Color"    : Ch_Color,
            "Prev"     : Prev_PT}
          Adj_Point.append(Proc_PT)
          Prev_PT = Proc_PT
    return Adj_Point


  # Function: GUI_GetScreenSize
  # Descript: 取得目前螢幕解析度大小
  def GUI_GetScreenSize(self):
    Screen   = QApplication.primaryScreen()
    Geometry = Screen.geometry()
    return Geometry.width(),Geometry.height()


  # Function: Menu_File_Load_Event
  # Descript: 處理檔案載入事件
  def Menu_File_Load_Event(self):
    File_Path,File_Filter = QFileDialog.getOpenFileName(self,"選擇 LOG 檔案",".","Log Files (*.log *.txt);;All Files (*)")
    if File_Path:
      Data = Parse_I2C_Data(File_Path)
      if Data:
        self.Current_Data = Data
        self.GUI_Plot_Update(Data,self.View_Mode)
        self.statusBar().showMessage(f"已載入檔案: {File_Path}",2000)
      else:
        self.statusBar().showMessage(f"解析失敗: {File_Path}",2000)


  # Function: Menu_File_Save_Event
  # Descript: 處理圖表檔案儲存事件
  def Menu_File_Save_Event(self):
    if not self.Current_Data:
      QMessageBox.warning(self,"警告","目前沒有可儲存的圖表資料！請先載入 Log 檔案。")
      return

    File_Path,File_Filter = QFileDialog.getSaveFileName(self,"儲存圖表",".","PNG Image (*.png);;JPEG Image (*.jpg);;PDF Document (*.pdf)")
    if File_Path:
      try:
        self.Canvas.figure.savefig(File_Path,dpi=300,bbox_inches='tight')
        self.statusBar().showMessage(f"圖表已成功儲存: {File_Path}",3000)
      except Exception as e:
        QMessageBox.critical(self,"錯誤",f"儲存檔案失敗！\n錯誤訊息: {e}")


  # Function: Menu_File_Exit_Event
  # Descript: 處理離開應用程式事件
  def Menu_File_Exit_Event(self):
    self.close()


  # Function: Menu_Info_Help_Event
  # Descript: 顯示操作說明對話框
  def Menu_Info_Help_Event(self):
    QMessageBox.information(self,"說明","【GUI Simulate I2C Monitor 說明】\n\n1. 點擊[檔案]->[載入]讀取 I2C Log\n2. 支援單圖與多圖模式切換\n3. 同時間點交錯操作會以不同通道色彩的箭頭區分順序")


  # Function: Menu_Info_About_Event
  # Descript: 顯示關於本軟體的資訊對話框
  def Menu_Info_About_Event(self):
    QMessageBox.about(self,"關於","GUI Simulate I2C Monitor\n版本: 2.6")


  # Function: Menu_View_Mode_Event
  # Descript: 處理檢視模式切換事件
  def Menu_View_Mode_Event(self,Mode):
    self.View_Mode = Mode
    if self.Current_Data:
      self.GUI_Plot_Update(self.Current_Data,self.View_Mode)


# Function: Load_StyleSheet
def Load_StyleSheet(App,FileName):
  try:
    with open(FileName,"r",encoding="utf-8") as File:
      App.setStyleSheet(File.read())
  except FileNotFoundError:
    pass


# Function: Parse_I2C_Data
# Descript: 解析 I2C Log 檔案內容
def Parse_I2C_Data(File_Path):
  Parse_Data = { "I2C": {} }
  Pattern = re.compile(r"^\s*(\d+)::\[(I2C-[^\]]+)\]:\s*\[([RW])\]\[([0-9A-Fa-f]+)\]\s*=\s*([0-9A-Fa-f]+)")

  try:
    with open(File_Path,"r",encoding="utf-8") as f:
      for Line in f:
        Match = Pattern.match(Line)
        if Match:
          Time_MS = int(Match.group(1))
          Device  = Match.group(2)
          RW_Type = Match.group(3)
          Reg     = Match.group(4)
          Val_Hex = Match.group(5)
          Val_Dec = int(Val_Hex,16)

          if Device not in Parse_Data["I2C"]:
            Parse_Data["I2C"][Device] = []

          Parse_Data["I2C"][Device].append({
            "Time" : Time_MS,
            "Value": Val_Dec,
            "Label": f"{RW_Type}[{Reg}h]:{Val_Hex}h"})
          
    print(f"[Success]: Parse I2C Log Data Success!!")
    return Parse_Data
    
  except Exception as e:
    print(f"[Error]: Parse Log Failed!!({e})")
    return None


# 主程序
if __name__ == "__main__":
  App = QApplication(sys.argv)
  Load_StyleSheet(App,CONFIG_STYLE_FILE)
  Win = GUI_GPIO_Window()
  Win.show()
  sys.exit(App.exec())