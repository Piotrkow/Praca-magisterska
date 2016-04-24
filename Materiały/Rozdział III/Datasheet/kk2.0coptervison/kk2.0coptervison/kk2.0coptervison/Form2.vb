Imports System
Imports System.Threading
Imports System.IO.Ports
Imports System.ComponentModel

Public Class Form2
    Const WM_CAP As Short = &H400S
    Const WM_CAP_DRIVER_CONNECT As Integer = WM_CAP + 10
    Const WM_CAP_DRIVER_DISCONNECT As Integer = WM_CAP + 11
    Const WM_CAP_EDIT_COPY As Integer = WM_CAP + 30
    Const WM_CAP_SET_PREVIEW As Integer = WM_CAP + 50
    Const WM_CAP_SET_PREVIEWRATE As Integer = WM_CAP + 52
    Const WM_CAP_SET_SCALE As Integer = WM_CAP + 53
    Const WS_CHILD As Integer = &H40000000
    Const WS_VISIBLE As Integer = &H10000000
    Const SWP_NOMOVE As Short = &H2S
    Const SWP_NOSIZE As Short = 1
    Const SWP_NOZORDER As Short = &H4S
    Const HWND_BOTTOM As Short = 1
    Dim iDevice As Integer = 0
    Dim hHwnd As Integer
    Declare Function SendMessage Lib "user32" Alias "SendMessageA" (ByVal hwnd As Integer, ByVal wMsg As Integer, ByVal wParam As Integer, ByVal lParam As Object) As Integer
    Declare Function SetWindowPos Lib "user32" Alias "SetWindowPos" (ByVal hwnd As Integer, ByVal hWndInsertAfter As Integer, ByVal x As Integer, ByVal y As Integer, ByVal cx As Integer, ByVal cy As Integer, ByVal wFlags As Integer) As Integer
    Declare Function DestroyWindow Lib "user32" (ByVal hndw As Integer) As Boolean
    Declare Function capCreateCaptureWindowA Lib "avicap32.dll" (ByVal lpszWindowName As String, ByVal dwStyle As Integer, ByVal x As Integer, ByVal y As Integer, ByVal nWidth As Integer, ByVal nHeight As Short, ByVal hWndParent As Integer, ByVal nID As Integer) As Integer
    Declare Function capGetDriverDescriptionA Lib "avicap32.dll" (ByVal wDriver As Short, ByVal lpszName As String, ByVal cbName As Integer, ByVal lpszVer As String, ByVal cbVer As Integer) As Boolean
    '------------------------------------------------
    Dim myPort As Array
    Delegate Sub SetTextCallback(ByVal [text] As String) 'Added to prevent threading errors during receiveing of data
    '------------------------------------------------

    Private Sub LoadDeviceList()
        Dim strName As String = Space(100)
        Dim strVer As String = Space(100)
        Dim bReturn As Boolean
        Dim x As Integer = 0
        Do
            bReturn = capGetDriverDescriptionA(x, strName, 100, strVer, 100)
            If bReturn Then lstDevices.Items.Add(strName.Trim)
            x += 1
        Loop Until bReturn = False
    End Sub
    Private Sub OpenPreviewWindow()
        Dim iHeight As Integer = picCapture.Height
        Dim iWidth As Integer = picCapture.Width
        hHwnd = capCreateCaptureWindowA(iDevice, WS_VISIBLE Or WS_CHILD, 0, 0, 640, 480, picCapture.Handle.ToInt32, 0)
        If SendMessage(hHwnd, WM_CAP_DRIVER_CONNECT, iDevice, 0) Then
            SendMessage(hHwnd, WM_CAP_SET_SCALE, True, 0)
            SendMessage(hHwnd, WM_CAP_SET_PREVIEWRATE, 66, 0)
            SendMessage(hHwnd, WM_CAP_SET_PREVIEW, True, 0)
            SetWindowPos(hHwnd, HWND_BOTTOM, 0, 0, picCapture.Width, picCapture.Height, SWP_NOMOVE Or SWP_NOZORDER)
            btnStop.Enabled = True
            btnStop.Enabled = True
            btnStart.Enabled = False
        Else
            DestroyWindow(hHwnd)
            btnStop.Enabled = False
        End If
    End Sub

    Private Sub ClosePreviewWindow()
        SendMessage(hHwnd, WM_CAP_DRIVER_DISCONNECT, iDevice, 0)
        DestroyWindow(hHwnd)
    End Sub
    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        myPort = IO.Ports.SerialPort.GetPortNames()
        ComboBox1.Items.AddRange(myPort)
        ComboBox4.Items.AddRange(myPort)
        Button1.Enabled = True
        Button23.Enabled = True
        LoadDeviceList()
    End Sub
    Private Sub btnStart_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnStart.Click
        OpenPreviewWindow()
        btnStart.Enabled = False
        btnStop.Enabled = True
    End Sub

    Private Sub btnStop_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnStop.Click
        ClosePreviewWindow()
        btnStart.Enabled = True
        btnStop.Enabled = False
    End Sub

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        SerialPort1.PortName = ComboBox1.Text
        SerialPort1.BaudRate = ComboBox2.Text
        SerialPort1.Close()
        SerialPort1.Open()
        SerialPort1.ReadTimeout = 1000
        Timer1.Enabled = True
        SerialPort1.DiscardInBuffer()
    End Sub

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        TextBox1.Text = SerialPort1.ReadTo(Chr(1))
        TextBox2.Text = SerialPort1.ReadTo(Chr(2))
        TextBox3.Text = SerialPort1.ReadTo(Chr(3))
        TextBox4.Text = SerialPort1.ReadTo(Chr(4))
        TextBox5.Text = SerialPort1.ReadTo(Chr(5))
        TextBox6.Text = SerialPort1.ReadTo(Chr(6))
        TextBox7.Text = SerialPort1.ReadTo(Chr(7))
        TextBox8.Text = SerialPort1.ReadTo(Chr(8))
        TextBox9.Text = SerialPort1.ReadTo(Chr(9))
        TextBox10.Text = SerialPort1.ReadTo(Chr(10))
        TextBox11.Text = SerialPort1.ReadTo(Chr(11))
        TextBox12.Text = SerialPort1.ReadTo(Chr(12))
        TextBox13.Text = SerialPort1.ReadTo(Chr(13))
        TextBox14.Text = SerialPort1.ReadTo(Chr(14))
        TextBox15.Text = SerialPort1.ReadTo(Chr(15))
        TextBox19.Text = SerialPort1.ReadTo(Chr(16))
        TextBox20.Text = SerialPort1.ReadTo(Chr(17))
        TextBox21.Text = SerialPort1.ReadTo(Chr(18))
        TextBox16.Text = SerialPort1.ReadTo(Chr(19))
        TextBox17.Text = SerialPort1.ReadTo(Chr(20))
        TextBox18.Text = SerialPort1.ReadTo(Chr(21))
        SerialPort1.DiscardInBuffer()
        If TextBox3.Text = 0 Then TextBox3.Text = 1000
        If TextBox2.Text = 0 Then TextBox2.Text = 1000
        If TextBox10.Text <= 0 Then TextBox10.Text = 13
        NumericUpDown1.Value = TextBox3.Text
        NumericUpDown2.Value = TextBox2.Text
        NumericUpDown3.Value = TextBox7.Text
        NumericUpDown5.Value = TextBox11.Text
        NumericUpDown6.Value = TextBox10.Text
        MyVerticalProgessBar5.Value = NumericUpDown1.Value
        MyVerticalProgessBar4.Value = NumericUpDown2.Value
        If NumericUpDown3.Value > 10000 Then NumericUpDown3.Value = 0
        MyVerticalProgessBar3.Value = NumericUpDown3.Value
        Label2.Text = TextBox3.Text
        If TextBox9.Text = "2" Then PictureBox1.Visible = True
        If TextBox9.Text = "2" Then Label16.Visible = True
        If TextBox9.Text = "1" Then Label16.Visible = True
        If TextBox6.Text = "1800" Then Label17.Text = "KK2.0 AUTO LEVEL ON"
        If TextBox6.Text = "1000" Then Label17.Text = "KK2.0 AUTO LEVEL OFF"
        If TextBox6.Text = "1000" Then Label17.ForeColor = Color.Red
        If TextBox6.Text = "1800" Then Label17.ForeColor = Color.GreenYellow


        If TextBox7.Text >= 0 Then Me.GRAPH1.Series("HEIGHT").Points.AddXY(TextBox7.Text, TextBox7.Text)
        If TextBox3.Text >= 0 Then Me.GRAPH1.Series("THROTTLE IN").Points.AddXY(TextBox3.Text, TextBox3.Text)
        If TextBox2.Text >= 0 Then Me.GRAPH1.Series("THROTTLE OUT").Points.AddXY(TextBox2.Text, TextBox2.Text)
        If TextBox19.Text = ("5") Then
            Button7.Enabled = True
            Button8.Enabled = True
            Label19.Visible = True
            Label1.Visible = False
        ElseIf TextBox19.Text = ("0") Then
            Button7.Enabled = False
            Button8.Enabled = False
            Label1.Visible = True
            Label19.Visible = False
        End If
        If TextBox20.Text = ("5") Then
            Button5.Enabled = True
            Button6.Enabled = True
            Label20.Visible = True
            Label21.Visible = False
        ElseIf TextBox20.Text = ("0") Then
            Button5.Enabled = False
            Button6.Enabled = False
            Label21.Visible = True
            Label20.Visible = False
        End If

        If TextBox21.Text = ("5") Then
            Button13.Enabled = False
            Button14.Enabled = False
            Button15.Enabled = False
            Button16.Enabled = False
            Button10.Enabled = False
            Button11.Enabled = False
            TextBox16.Enabled = False
            TextBox17.Enabled = False
            TextBox18.Enabled = False
            Button5.Enabled = True
            Button6.Enabled = True
            Button21.Enabled = True
            TextBox12.Enabled = True
        ElseIf TextBox21.Text = ("0") Then
            Button13.Enabled = True
            Button14.Enabled = True
            Button15.Enabled = True
            Button16.Enabled = True
            Button10.Enabled = True
            Button11.Enabled = True
            TextBox16.Enabled = True
            TextBox17.Enabled = True
            TextBox18.Enabled = True
            Button5.Enabled = False
            Button6.Enabled = False
            Button21.Enabled = False
            TextBox12.Enabled = False

        End If
    End Sub
    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        SerialPort1.Close()
        Form1.Close()
        Application.Exit()
    End Sub

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
        SerialPort1.WriteLine(3)
        SerialPort1.WriteLine(9)
    End Sub

    Private Sub Button4_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button4.Click
        SerialPort1.WriteLine(2)
        SerialPort1.WriteLine(9)
    End Sub

    Private Sub Button6_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button6.MouseClick
        SerialPort1.WriteLine(5)
        SerialPort1.WriteLine(9)
    End Sub

    Private Sub Button5_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button5.MouseClick
        SerialPort1.WriteLine(4)
        SerialPort1.WriteLine(9)
    End Sub

    Private Sub Button9_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button9.MouseClick
        SerialPort1.WriteLine(1)
        SerialPort1.WriteLine(9)
    End Sub

    Private Sub Button11_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button11.MouseClick
        SerialPort1.WriteLine(8)
        SerialPort1.WriteLine(9)
    End Sub

    Private Sub Button10_CLick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button10.Click
        SerialPort1.WriteLine("o")
        SerialPort1.WriteLine(9)
    End Sub

    Private Sub Button11_Click_1(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button11.Click
        SerialPort1.WriteLine("u")
        SerialPort1.WriteLine(9)
    End Sub

    Private Sub Button12_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button12.MouseHover
        SerialPort1.WriteLine(9)
        SerialPort1.WriteLine(8)
        SerialPort1.WriteLine(9)
        SerialPort1.WriteLine(9)
        SerialPort1.WriteLine(8)
    End Sub
    Private Sub Button14_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button14.Click
        SerialPort1.WriteLine("K")
        SerialPort1.WriteLine(9)
    End Sub

    Private Sub Button13_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button13.Click
        SerialPort1.WriteLine("L")
        SerialPort1.WriteLine(9)
    End Sub

    Private Sub Button16_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button16.Click
        SerialPort1.WriteLine("F")
        SerialPort1.WriteLine(9)
    End Sub

    Private Sub Button15_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button15.Click
        SerialPort1.WriteLine("R")
        SerialPort1.WriteLine(9)
    End Sub

    Private Sub Button20_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button20.Click
        SerialPort1.WriteLine("g")
        SerialPort1.WriteLine(9)
    End Sub

    Private Sub Button21_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button21.Click
        SerialPort1.WriteLine("h")
        SerialPort1.WriteLine(9)
    End Sub

    Private Sub Button8_Click_1(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button8.Click
        SerialPort1.WriteLine("j")
        SerialPort1.WriteLine(9)
    End Sub

    Private Sub Button7_Click_1(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button7.Click
        SerialPort1.WriteLine("^")
        SerialPort1.WriteLine(9)
    End Sub

    Private Sub Button22_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button22.Click
        SerialPort1.WriteLine("A")
        SerialPort1.WriteLine(9)
    End Sub

    Private Sub Button23_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button23.Click
        SerialPort2.PortName = ComboBox4.Text
        SerialPort2.BaudRate = ComboBox3.Text
        SerialPort2.Close()
        SerialPort2.Open()
        SerialPort2.ReadTimeout = 1000
        Timer2.Enabled = True
        SerialPort2.DiscardInBuffer()
    End Sub

    Private Sub Timer2_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer2.Tick
        TextBox22.Text = SerialPort2.ReadTo(Chr(1))
        TextBox23.Text = SerialPort2.ReadTo(Chr(2))
        TextBox24.Text = SerialPort2.ReadTo(Chr(3))
        TextBox25.Text = SerialPort2.ReadTo(Chr(4))
        If TextBox23.Text = "5" Then Label24.Visible = True
        If TextBox23.Text = "5" Then Label24.Text = ("FUNCTION 1")
        If TextBox24.Text = "5" Then Label24.Visible = True
        If TextBox24.Text = "5" Then Label24.Text = ("FUNCTION 2")
        If TextBox25.Text = "5" Then Label24.Visible = True
        If TextBox25.Text = "5" Then Label24.Text = ("FUNCTION 3")
        If TextBox23.Text = "5" Then Button12.PerformClick()
        If TextBox24.Text = "5" Then Button12.PerformClick()
        If TextBox25.Text = "5" Then Button12.PerformClick()
        SerialPort2.DiscardInBuffer()
    End Sub

    Private Sub Button17_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button17.Click
        SerialPort1.WriteLine(6)
        SerialPort1.WriteLine(9)
    End Sub

    Private Sub Button18_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button18.Click
        SerialPort1.WriteLine(7)
        SerialPort1.WriteLine(9)
    End Sub

    Private Sub Button19_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button19.Click
        SerialPort1.WriteLine(9)
        SerialPort1.WriteLine(8)
        SerialPort1.WriteLine(9)
        SerialPort1.WriteLine(9)
        SerialPort1.WriteLine(8)
    End Sub
End Class
