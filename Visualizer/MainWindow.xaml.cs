using System;
using System.Collections.Generic;
using System.Diagnostics;
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
using ManagedPlusPlusWrapper;

namespace Visualizer
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private static uint[,] _operators = { {(int)OperatorsTypes.Zero, 0, 0, 0, 0 }, 
                                            { (int)OperatorsTypes.ExternalOutput, 3, 0, 0, 0 }, 
                                            { (int)OperatorsTypes.ExternalInput, 0, 0, 0, 2 } /*, 
                                            { (int)OperatorsTypes.Equal, 2, 0, 0, 0 }*/ };
        private Point[] _opersPoints;
        private Entity _entity;
        private readonly uint _lastOperatorNumber;
        private Canvas _canvas;
        private Ellipse _operatorEllipse;
        private const ushort OperatorRadius = 50;
        private const ushort ConnectionDotD = 6;
        private const ushort OperatorDiametr = OperatorRadius * 2;
        private const ushort ArrowLenth = 20;

        public MainWindow()
        {
            try
            {
               // _entity = Entity.GenerateEntity();
                _entity = GenerateTestEntity();
             
                _entity.DumpEntity();
                _operators = _entity.Operators;
                _opersPoints = new Point[_operators.GetLength(0)];
                InitializeComponent();
                InitOper();
                _lastOperatorNumber = (uint) GetOperatorsCount();
                _canvas = new Canvas();
                DrawOperators();
                DrawConnectionsAndValues();
            }
            catch (Exception ex)
            {
                Debug.Write(ex);
            }
        }

        private Entity GenerateTestEntity()
        {
            var entS = new EntityS(7);

            var entity = new Entity(entS);

            entity.Operators[1, 0] = (int)OperatorsTypes.ExternalOutput;
            entity.Operators[2, 0] = (int)OperatorsTypes.ExternalOutput;
            entity.Operators[3, 0] = (int)OperatorsTypes.ExternalOutput;
            entity.Operators[4, 0] = (int)OperatorsTypes.ExternalOutput;
            entity.Operators[5, 0] = (int)OperatorsTypes.ExternalInput;

            entity.Operators[6, 0] = (int)OperatorsTypes.If;
            entity.Operators[6, 1] = 1;
            entity.Operators[6, 2] = 2;
            entity.Operators[6, 3] = 3;
            entity.Operators[6, 4] = 4;

            entity.Operators[5, 1] = 6;

    return entity;
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

        private Ellipse GetDot(SolidColorBrush br)
        {
            var dotEllipse = new Ellipse();
            var mySolidColorBrush = new SolidColorBrush { Color = Color.FromArgb(255, 0, 0, 0) };
            dotEllipse.Fill = mySolidColorBrush;
            dotEllipse.StrokeThickness = 1;
            dotEllipse.Stroke = br;
            dotEllipse.Width = ConnectionDotD;
            dotEllipse.Height = ConnectionDotD;
            return dotEllipse;
        }

        private int GetOperatorsCount()
        {
            for (int i = 1; i < _operators.GetUpperBound(0); i++)
            {
                if (_operators[i, 0] == (int)OperatorsTypes.Zero) 
                    return i;
            }
            return _operators.GetUpperBound(0);
        }

        private void DrawOperators()
        {
            double dw = Math.Sqrt(_lastOperatorNumber);
            var gridDim = (uint)Math.Round(dw);

            for (uint i = 1; i < _entity.NextOperatorId; i++)
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
                var operText = new TextBlock(new Run(Entity.GetOperName((OperatorsTypes)_operators[i, 0])));
                OperatorsCanvas.Children.Add(operText);
                Canvas.SetLeft(operText, xd + 3);
                Canvas.SetTop(operText, yd + OperatorRadius -  operText.FontSize);

                var operNumbText = new TextBlock(new Run("№" + i.ToString()));
                operNumbText.Foreground = new SolidColorBrush(Colors.Blue);
                OperatorsCanvas.Children.Add(operNumbText);
                Canvas.SetLeft(operNumbText, xd + OperatorRadius);
                Canvas.SetTop(operNumbText, yd + OperatorRadius);

            }
        }

        private void DrawConnectionsAndValues()
        {
            for (int currentOperator = 1; currentOperator < _entity.NextOperatorId; currentOperator++)
            {
                for (int contact = EntityConsts.FirstContact; contact <= EntityConsts.contactsCount; contact++)
                {
                    var fromOper = (int)_operators[currentOperator, contact];
                    if (fromOper != 0)
                    {
                        DrawConnectionAndValue(fromOper, currentOperator, contact);
                    }
                }
            }
        }

        private void DrawConnectionAndValue(int fromOper, int toOper, int toOperContactId)
        {
            Point fromP = GetKontactPoint(fromOper, EntityConsts.outputValueColumn);
            DrawConnectionPoint(fromP, Brushes.Black);

            Point toP = GetKontactPoint(toOper, toOperContactId);
            DrawConnectionPoint(toP, Brushes.Red);

            Shape linkArrow = DrawLinkArrow(fromP, toP);
            OperatorsCanvas.Children.Add(linkArrow);

            uint val = _operators[fromOper, EntityConsts.outputValueColumn];
            DrawValue(fromP, val.ToString(), Colors.Brown, 15); // Output value
            DrawValue(toP, toOperContactId.ToString(), Colors.CadetBlue, 10);  // Contact id
        }

        private static Shape DrawLinkArrow(Point p1, Point p2)
        {
            var lineGroup = new GeometryGroup();
            double theta = Math.Atan2((p2.Y - p1.Y), (p2.X - p1.X)) * 180 / Math.PI;

            var pathGeometry = new PathGeometry();
            var pathFigure = new PathFigure();
            var p = new Point(p1.X + ((p2.X - p1.X) / 1.35), p1.Y + ((p2.Y - p1.Y) / 1.35));
            pathFigure.StartPoint = p;

            var lpoint = new Point(p.X + 6, p.Y + 15);
            var rpoint = new Point(p.X - 6, p.Y + 15);
            var seg1 = new LineSegment {Point = lpoint};
            pathFigure.Segments.Add(seg1);

            var seg2 = new LineSegment {Point = rpoint};
            pathFigure.Segments.Add(seg2);

            var seg3 = new LineSegment {Point = p};
            pathFigure.Segments.Add(seg3);

            pathGeometry.Figures.Add(pathFigure);
            var transform = new RotateTransform {Angle = theta + 90, CenterX = p.X, CenterY = p.Y};
            pathGeometry.Transform = transform;
            lineGroup.Children.Add(pathGeometry);

            var connectorGeometry = new LineGeometry {StartPoint = p1, EndPoint = p2};
            lineGroup.Children.Add(connectorGeometry);
            var path = new System.Windows.Shapes.Path {Data = lineGroup, StrokeThickness = 2};
            path.Stroke = path.Fill = Brushes.Blue;

            return path;
        }

        private void DrawValue(Point pnt, string valueToSet, Color col, double fontSize)
        {
            var operText = new TextBlock(new Run(valueToSet)) 
            { 
                Foreground = new SolidColorBrush(col), 
                FontSize = fontSize 
            };
            OperatorsCanvas.Children.Add(operText);
            Canvas.SetLeft(operText, pnt.X);
            Canvas.SetTop(operText, pnt.Y);
        }
     
        private void DrawConnectionPoint(Point pt, SolidColorBrush br)
        {
            var dotC = GetDot(br);
            OperatorsCanvas.Children.Add(dotC);
            Canvas.SetLeft(dotC, pt.X - ConnectionDotD / 2);
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
                case 1: //       _/)
                    celX = cx + OperatorRadius * Math.Cos(Math.PI / 4);
                    celY = cy + OperatorRadius * Math.Sin(Math.PI / 4);
                    break;
                case 2://       -)
                    celX = cx + OperatorRadius;
                    celY = cy;
                    break;
                case 3://       \)
                    celX = cx + OperatorRadius * Math.Cos(Math.PI / 4);
                    celY = cy - OperatorRadius * Math.Sin(Math.PI / 4);
                    break;
                case 4://       /)
                    celX = cx;
                    celY = cy - OperatorRadius;
                    break;
                case 5://       -(
                    celX = cx - OperatorRadius;
                    celY = cy;
                    break;
                default:
                    throw new NotImplementedException("Not implemented contactId");
            }

            return new Point(celX, celY);
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

        private void TranslateYSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            int one = 1;
        }
    }
}
