
Public Class ArtificialHorizon

    Private g As Graphics

    Private _roll_angle As Double
    Public Property roll_angle() As Double
        Get
            Return _roll_angle
        End Get
        Set(ByVal value As Double)
            _roll_angle = value
            Invalidate()
        End Set
    End Property
    Private _pitch_angle As Double
    Public Property pitch_angle() As Double
        Get
            Return _pitch_angle
        End Get
        Set(ByVal value As Double)
            _pitch_angle = value
            Invalidate()
        End Set
    End Property


    Private Sub ArtificialHorizon_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load

    End Sub

    Private Function pitch_to_pix(ByVal pitch As Double) As Integer
        Return pitch / 35.0 * Me.Height / 2
        'Return pitch / 45.0 * Me.Height / 2
    End Function

    Private Sub ArtificialHorizon_Paint(ByVal sender As Object, ByVal e As System.Windows.Forms.PaintEventArgs) Handles Me.Paint
        g = e.Graphics
        g.SmoothingMode = Drawing2D.SmoothingMode.HighQuality

        g.Clear(Me.BackColor)
        Dim sin As Double = Math.Sin(roll_angle / 180 * 3.14)

        g.ResetTransform()
        '        g.FillRegion(Brushes.White, New Region(New Rectangle(0, 0, Me.Width, Me.Height)))

        ' rounded rectangle
        Dim path As New Drawing2D.GraphicsPath()
        Dim r As Single = 50
        path.AddArc(0, 0, r, r, 180, 90)
        path.AddArc(Me.Width - r, 0, r, r, 270, 90)
        path.AddArc(Me.Width - r, Me.Height - r, r, r, 0, 90)
        path.AddArc(0, Me.Height - r, r, r, 90, 90)
        'path.AddEllipse(0, 0, Me.Width, Me.Height)
        path.CloseFigure()
        g.SetClip(path)

        g.TranslateTransform(Me.Width / 2, Me.Height / 2)

        g.RotateTransform(roll_angle)
        g.TranslateTransform(0, pitch_to_pix(pitch_angle))

        ' chocolate
        Dim b As New System.Drawing.Drawing2D.LinearGradientBrush(New RectangleF(-Me.Width, 0, Me.Height * 2, Me.Width * 2), Color.FromArgb(255, 219, 140, 21), Color.Brown, Drawing2D.LinearGradientMode.Vertical)
        g.FillRectangle(b, New RectangleF(-Me.Width * 2, +1, Me.Height * 4, Me.Width * 4))

        g.RotateTransform(180)

        ' color.aqua
        b = New System.Drawing.Drawing2D.LinearGradientBrush(New RectangleF(-Me.Width, -1, Me.Height * 2, Me.Width * 2), Color.FromArgb(255, 28, 134, 186), Color.DarkBlue, Drawing2D.LinearGradientMode.Vertical)
        g.FillRectangle(b, New RectangleF(-Me.Width * 2, 0, Me.Height * 4, Me.Width * 4))




        g.ResetTransform()
        Dim w2 As Single = Me.Width / 2
        Dim s As Single = Me.Width / 38
        g.TranslateTransform(Me.Width / 2, Me.Height / 2)
        g.RotateTransform(45)
        g.TranslateTransform(-w2 + s, 0)
        g.DrawLine(New Pen(Color.White, 2), 0, 0, s * 2, 0)
        g.TranslateTransform(+w2 - s, 0)
        g.RotateTransform(15)
        g.DrawLine(New Pen(Color.White, 2), -w2 + s, 0, -w2 + s * 2, 0)
        g.RotateTransform(15)
        g.DrawLine(New Pen(Color.White, 2), -w2 + s, 0, -w2 + s * 2, 0)
        g.RotateTransform(15)
        g.DrawLine(New Pen(Color.White, 2), -w2 + s, 0, -w2 + s * 3, 0)
        'g.DrawString("0°", New System.Drawing.Font("sans-serif", 9), Brushes.White, -w2 + 40, -4)
        g.RotateTransform(15)
        g.DrawLine(New Pen(Color.White, 2), -w2 + s, 0, -w2 + s * 2, 0)
        g.RotateTransform(15)
        g.DrawLine(New Pen(Color.White, 2), -w2 + s, 0, -w2 + s * 2, 0)
        g.RotateTransform(15)
        g.DrawLine(New Pen(Color.White, 2), -w2 + s, 0, -w2 + s * 3, 0)
        'g.DrawString("+45°", New System.Drawing.Font("sans-serif", 9), Brushes.White, -w2 + 40, -4)


        g.ResetTransform()

        Dim length As Single = Me.Width / 4
        Dim notch As Single = Me.Width / 30
        g.TranslateTransform(Me.Width / 2, Me.Height / 2)
        g.DrawLine(New Pen(Color.White, 3), -length + notch * 2, 0, -notch, 0)
        g.DrawLine(New Pen(Color.White, 3), notch, 0, length - notch * 2, 0)
        g.DrawArc(New Pen(Color.White, 3), -notch, -notch, notch * 2, notch * 2, 180, -180)

        g.ResetTransform()

        ' driehoekje
        Dim ww As Single = Me.Width / 38
        g.TranslateTransform(Me.Width / 2, Me.Height / 2)
        g.RotateTransform(-90 + roll_angle)
        path = New Drawing2D.GraphicsPath()
        path.AddLine(w2 - ww * 3, 0, w2 - ww * 4, ww)
        path.AddLine(w2 - ww * 4, -ww, w2 - ww * 4, ww)
        path.AddLine(w2 - ww * 4, -ww, w2 - ww * 3, 0)
        g.FillRegion(Brushes.White, New Region(path))
        g.DrawLine(New Pen(Color.White, 1), w2 - ww * 3, 0, w2 - ww * 4, ww)
        g.DrawLine(New Pen(Color.White, 1), w2 - ww * 4, -ww, w2 - ww * 4, ww)
        g.DrawLine(New Pen(Color.White, 1), w2 - ww * 4, -ww, w2 - ww * 3, 0)



        g.ResetTransform()
        g.ResetClip()
        path = New Drawing2D.GraphicsPath()
        path.AddPie(New Rectangle(ww * 3, ww * 3, Me.Width - ww * 6, Me.Height - ww * 6), 0, 360)
        g.SetClip(path)

        g.TranslateTransform(Me.Width / 2, Me.Height / 2)
        g.RotateTransform(roll_angle)
        g.TranslateTransform(0, pitch_to_pix(pitch_angle))
        For i As Integer = -80 To 80 Step 10
            drawpitchline(g, i)
        Next i

    End Sub

    Private Sub drawpitchline(ByVal g As Graphics, ByVal pitch As Double)
        Dim w As Single = Me.Width / 8
        g.DrawLine(Pens.White, -w, pitch_to_pix(-pitch + 5), w, pitch_to_pix(-pitch + 5))
        g.DrawLine(Pens.White, -w * 5 / 3, pitch_to_pix(-pitch), w * 5 / 3, pitch_to_pix(-pitch))
        g.DrawString(pitch, Me.Font, Brushes.White, -w * 75 / 30, pitch_to_pix(-pitch) - 5)
        g.DrawString(pitch, Me.Font, Brushes.White, w * 2, pitch_to_pix(-pitch) - 5)
    End Sub

    Private Sub drawrollline(ByVal g As Graphics, ByVal a As Single)
        Dim w2 As Single = Me.Width / 2


        g.RotateTransform(a + 90)
        g.TranslateTransform(-w2 + 10, 0)
        g.DrawLine(Pens.White, 0, 0, 20, 0)
        g.TranslateTransform(10, 5)
        g.RotateTransform(-a - 90)
        g.DrawString("" & (a) & "°", New System.Drawing.Font("sans-serif", 9), Brushes.White, 0, 0)
        g.RotateTransform(+90 + a)
        g.TranslateTransform(-10, -5)
        g.TranslateTransform(+w2 - 10, 0)
        g.RotateTransform(-a - 90)
    End Sub
End Class
