using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
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
        uint[,] _operators = new uint[,] { { 1, 2 }, { 3, 4 }, { 5, 6 }, { 7, 8 }, { 1, 8 }, { 7, 8 }, { 0, 8 } };
        private uint _lastOperatorNumber;
        private Canvas _canvas;
        private Ellipse _operatorEllipse;
        private const ushort _operatorRadius = 50;

        public MainWindow()
        {
            InitializeComponent();
            InitOper();

            _lastOperatorNumber = (uint)GetOperatorsCount();

            _canvas = new Canvas();
            DrawOperators();


           
            

            this.Content = _canvas;
        }

        void InitOper()
        {
            _operatorEllipse = new Ellipse();
            // Create a SolidColorBrush with a red color to fill the  
            // Ellipse with.
            SolidColorBrush mySolidColorBrush = new SolidColorBrush();

            // Describes the brush's color using RGB values.  
            // Each value has a range of 0-255.
            mySolidColorBrush.Color = Color.FromArgb(255, 255, 255, 0);
            _operatorEllipse.Fill = mySolidColorBrush;
            _operatorEllipse.StrokeThickness = 1;
            _operatorEllipse.Stroke = Brushes.Black;

            // Set the width and height of the Ellipse.
            _operatorEllipse.Width = _operatorRadius;
            _operatorEllipse.Height = _operatorRadius;
        }

        int GetOperatorsCount()
        {
            for (int i = 0; i < _operators.GetUpperBound(0); i++)
            {
                if (_operators[i, 0] == 0) //Zero operator
                    return i;
            }
            return _operators.GetUpperBound(0);
        }

        void DrawOperators()
        {
            uint row, column;
            double dw = Math.Sqrt(_lastOperatorNumber);
            uint gridDim = (uint)Math.Round(dw);

            for (uint i = 0; i <= _operators.GetUpperBound(0); i++)
            {
                row = i / gridDim;
                column = i - row*gridDim;
                Ellipse curOperElips = XamlClone(_operatorEllipse);
                _canvas.Children.Add(curOperElips);
                Canvas.SetLeft(curOperElips, 2 * column * _operatorRadius);
                Canvas.SetTop(curOperElips, 2 * row * _operatorRadius);

            }
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
