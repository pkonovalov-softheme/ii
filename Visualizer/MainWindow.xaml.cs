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

namespace Visualizer
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private static readonly int[,] Operators = { { 0, 0, 0, 0, 0 }, { 1, 0, 0, 0, 4 }, { 2, 1, 1, 0, 0 }, { 3, 1, 2, 0, 0 }};
        private Point[] _opersPoints = new Point[Operators.GetLength(0)];
        private const ushort MaxOperatorsCount = 3;
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

        public MainWindow()
        {
            InitializeComponent();
            InitOper();
 


            _lastOperatorNumber = (uint)GetOperatorsCount();

            _canvas = new Canvas();
            DrawOperators();
            DrawConnections();

            //this.operatorsContent = _canvas;

        }

        private void InitOper()
        {
            _operatorEllipse = new Ellipse();
            // Create a SolidColorBrush with a red color to fill the  
            // Ellipse with.
            var mySolidColorBrush = new SolidColorBrush {Color = Color.FromArgb(255, 255, 255, 0)};

            // Describes the brush's color using RGB values.  
            // Each value has a range of 0-255.
            _operatorEllipse.Fill = mySolidColorBrush;
            _operatorEllipse.StrokeThickness = 1;
            _operatorEllipse.Stroke = Brushes.Black;

            // Set the width and height of the Ellipse.
            _operatorEllipse.Width = OperatorRadius;
            _operatorEllipse.Height = OperatorRadius;
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
                uint row = i / gridDim;
                uint column = i - row*gridDim;
                Ellipse curOperElips = XamlClone(_operatorEllipse);
                this.OperatorsCanvas.Children.Add(curOperElips);
                uint xd = 2 * row * OperatorRadius;
                uint yd = 2*column*OperatorRadius;
                var pt = new Point(xd - OperatorRadius, yd - OperatorRadius);// coordinates of the operator's center
                _opersPoints[i] = pt;
                Canvas.SetLeft(curOperElips, xd);
                Canvas.SetTop(curOperElips, yd);
                var operText = new TextBlock(new Run(GetOperName((OperatorsTypes)Operators[i, 0])));

                this.OperatorsCanvas.Children.Add(operText);
                Canvas.SetLeft(operText, xd + 3);
                Canvas.SetTop(operText, yd + OperatorRadius / 2 - operText.FontSize);
            }
        }

        private void DrawConnections()
        {
            for (int row = 1; row <= Operators.GetUpperBound(0); row++)
            {
                for (int column = 1; column <= MaxOperatorsCount; column++)
                {
                    var fromOper = Operators[row, column];
                    if ((fromOper != (int) OperatorsTypes.Zero) && (fromOper != (int) OperatorsTypes.Nothing))
                    {
                        DrawConnection(fromOper, row, column);
                    }
                }
            }
        }

        private void DrawConnection(int fromOper, int toOper, int toOperContactId)
        {
            Point fromP = GetKontactPoint(fromOper, 4);
            Point toP = GetKontactPoint(toOper, toOperContactId);
            var connectionL = new Line
            {
                Stroke = System.Windows.Media.Brushes.LightSteelBlue,
                X1 = fromP.X,
                Y1 = fromP.Y,
                X2 = toP.X,
                Y2 = toP.Y
            };
            this.OperatorsCanvas.Children.Add(connectionL);
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
                    throw new NotImplementedException("Not implimented contactId");
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
