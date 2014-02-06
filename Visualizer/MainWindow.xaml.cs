using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Runtime.InteropServices;
using NativeWrapper;

namespace Visualizer
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private static readonly int[,] Operators = { { (int)OperatorsTypes.Zero, 0, 0, 0, 0 }, { (int)OperatorsTypes.Equal, 0, 0, 0, 1 }, { (int)OperatorsTypes.Equal, 0, 0, 0, 2 }, { (int)OperatorsTypes.Plus, 1, 2, 0, 0 } };
        private readonly Point[] _opersPoints = new Point[Operators.GetLength(0)];
        private const ushort MaxOperatorsCount = 3;
        private const ushort OperatorValueColumn = 4;
        private enum OperatorsTypes
        {
            /*Zero is restricted system value. After the first zero operator _operators array processing will be stopped. 
            Value of the zero operator is assuming as zero-only.
            Basic operators:*/
            Zero, Divis, Equal, If, Minus, Multipl, One, Plus, Random, Time,
            //Meta operators:
            CreateChan, CreateOper, DelChan, GetOperType, IsChanExists,
            RemoveOperr, GetInpOperId, GetOperContCount, Nothing
        };
        private readonly uint _lastOperatorNumber;
        private Canvas _canvas;
        private Ellipse _operatorEllipse;
        private const ushort OperatorRadius = 50;
        private const ushort ConnectionDotD = 6;
        private const ushort OperatorDiametr = OperatorRadius * 2;
        private const ushort ArrowLenth = 20;

        public MainWindow()
        {
            InitializeComponent();
            InitOper();
            _lastOperatorNumber = (uint)GetOperatorsCount();
            _canvas = new Canvas();
            DrawOperators();
            DrawConnectionsAndValues();
        }

        private void InitOper()
        {
            _operatorEllipse = new Ellipse();
            var mySolidColorBrush = new SolidColorBrush {Color = Color.FromArgb(255, 255, 255, 0)};
            _operatorEllipse.Fill = mySolidColorBrush;
            _operatorEllipse.StrokeThickness = 1;
            _operatorEllipse.Stroke = Brushes.Black;
            _operatorEllipse.Width = OperatorDiametr;
            _operatorEllipse.Height = OperatorDiametr;
        }

        private Ellipse GetDot()
        {
            var dotEllipse = new Ellipse();
            var mySolidColorBrush = new SolidColorBrush { Color = Color.FromArgb(255, 0, 0, 0) };
            dotEllipse.Fill = mySolidColorBrush;
            dotEllipse.StrokeThickness = 1;
            dotEllipse.Stroke = Brushes.Black;
            dotEllipse.Width = ConnectionDotD;
            dotEllipse.Height = ConnectionDotD;
            return dotEllipse;
        }

        private int GetOperatorsCount()
        {
            for (int i = 1; i < Operators.GetUpperBound(0); i++)
            {
                if (Operators[i, 0] == (int)OperatorsTypes.Zero) 
                    return i;
            }
            return Operators.GetUpperBound(0);
        }

        private void DrawOperators()
        {
            double dw = Math.Sqrt(_lastOperatorNumber);
            uint gridDim = (uint)Math.Round(dw);

            for (uint i = 1; i <= Operators.GetUpperBound(0); i++)
            {
                uint row = (i - 1) / gridDim; // -1 Because we will miss first always Zero operator
                uint column = (i - 1) - row*gridDim;
                Ellipse curOperElips = XamlClone(_operatorEllipse);
                OperatorsCanvas.Children.Add(curOperElips);
                uint xd = 2 * row * OperatorDiametr;
                uint yd = 2 * column * OperatorDiametr;
                var pt = new Point(xd + OperatorRadius, yd + OperatorRadius);// coordinates of the operator's center
                _opersPoints[i] = pt;
                Canvas.SetLeft(curOperElips, xd);
                Canvas.SetTop(curOperElips, yd);
                var operText = new TextBlock(new Run(GetOperName((OperatorsTypes)Operators[i, 0])));
                OperatorsCanvas.Children.Add(operText);
                Canvas.SetLeft(operText, xd + 3);
                Canvas.SetTop(operText, yd + OperatorRadius -  operText.FontSize);
            }
        }

        private void DrawConnectionsAndValues()
        {
            for (int row = 1; row <= Operators.GetUpperBound(0); row++)
            {
                for (int column = 1; column <= MaxOperatorsCount; column++)
                {
                    var fromOper = Operators[row, column];
                    if ((fromOper != (int) OperatorsTypes.Zero) && (fromOper != (int) OperatorsTypes.Nothing))
                    {
                        DrawConnectionAndValue(fromOper, row, column);
                    }
                }
            }
        }

        private void DrawConnectionAndValue(int fromOper, int toOper, int toOperContactId)
        {
            Point fromP = GetKontactPoint(fromOper, 4);
            DrawConnectionPoint(fromP);
            Point toP = GetKontactPoint(toOper, toOperContactId);
            DrawConnectionPoint(toP);
            var connectionL = new Line
            {
                Stroke = System.Windows.Media.Brushes.Blue,
                X1 = fromP.X,
                Y1 = fromP.Y,
                X2 = toP.X,
                Y2 = toP.Y,
                StrokeThickness = 1
            };
            OperatorsCanvas.Children.Add(connectionL);

            var val = Operators[fromOper, OperatorValueColumn];
            DrawValue(fromP, toP, val);
        }

        private void DrawValue(Point fromP, Point toP, int valueToSet)
        {
            //double dx = toP.X - fromP.X;
            //double dy = toP.Y - fromP.Y;

            //double lineLenth = Math.Sqrt(dx*dx + dy*dy);
            //double lineXangel = Math.Acos(dx/lineLenth);

            //double xMidl = fromP.X + lineLenth  * Math.Cos(lineXangel);
            //double yMidl = fromP.Y + lineLenth  * Math.Sin(lineXangel);

            //var operText = new TextBlock(new Run(valueToSet.ToString()));
            //OperatorsCanvas.Children.Add(operText);
            //Canvas.SetLeft(operText, xMidl);
            //Canvas.SetTop(operText, yMidl);
            var operText = new TextBlock(new Run(valueToSet.ToString()));
            OperatorsCanvas.Children.Add(operText);
            Canvas.SetLeft(operText, fromP.X);
            Canvas.SetTop(operText, fromP.Y);
        }
        //not working
        //private void DrawMidlArrow(Point fromP, Point toP)
        //{
        //    double dx = toP.X - fromP.X;
        //    double dy = toP.Y - fromP.Y;

        //    double lineLenth = Math.Sqrt(dx*dx + dy*dy);
        //    double lineXangel = Math.Acos(dx/lineLenth);

        //    double xMidl = (dx/2) * Math.Cos(lineXangel);
        //    double yMidl = (dy/2) * Math.Sin(lineXangel);
        //    double compAngle = Math.PI/2 - lineXangel;
        //    double arrowAngle = compAngle - Math.PI/4;
        //    double arrowEndX = xMidl - ArrowLenth * Math.Cos(arrowAngle);
        //    double arrowEndY = yMidl - ArrowLenth * Math.Cos(arrowAngle);
        //    var connectionL = new Line
        //    {
        //        Stroke = System.Windows.Media.Brushes.Red,
        //        X1 = xMidl,
        //        Y1 = yMidl,
        //        X2 = arrowEndX,
        //        Y2 = arrowEndY,
        //        StrokeThickness = 1
        //    };
        //    this.OperatorsCanvas.Children.Add(connectionL);

        //}

        private void DrawConnectionPoint(Point pt)
        {
            var dotC = GetDot();
            OperatorsCanvas.Children.Add(dotC);
            Canvas.SetLeft(dotC, pt.X - ConnectionDotD/2);
            Canvas.SetTop(dotC, pt.Y - ConnectionDotD / 2);
        }

        private Point GetKontactPoint(int oper, int contactId)
        {
            //Centr of circle
            double cx = _opersPoints[oper].X;
            double cy = _opersPoints[oper].Y;

            double celX, celY;

            switch (contactId)
            {
                case 1: //       /)
                    celX = cx + OperatorRadius * Math.Cos(Math.PI / 4);
                    celY = cy + OperatorRadius * Math.Sin(Math.PI / 4);
                    break;
                case 2://       -)
                    celX = cx + OperatorRadius;
                    celY = cy;
                    break;
                case 3://       \)
                    celX = cx - OperatorRadius * Math.Cos(Math.PI / 4);
                    celY = cy - OperatorRadius * Math.Sin(Math.PI / 4);
                    break;
                case 4://       -(
                    celX = cx - OperatorRadius;
                    celY = cy;
                    break;
                default:
                    throw new NotImplementedException("Not implemented contactId");
            }

            return new Point(celX, celY);
        }

        private string GetOperName(OperatorsTypes op)
        {
            return Enum.GetName(typeof(OperatorsTypes), op);
        }

        public T XamlClone<T>(T source)
        {
            string savedObject = System.Windows.Markup.XamlWriter.Save(source);

            // Load the XamlObject
            var stringReader = new StringReader(savedObject);
            System.Xml.XmlReader xmlReader = System.Xml.XmlReader.Create(stringReader);
            T target = (T)System.Windows.Markup.XamlReader.Load(xmlReader);

            return target;
        }
    }
}
