using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace ai3
{
    public partial class Form1 : Form
    {

        public Form1()
        {
            InitializeComponent();
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            Graphics gr=e.Graphics;

            constants con = new constants();
            int kolObektovMira = 20;
            Mir curM = new Mir(con);
            curM.maxEx = kolObektovMira * 3;//??????
            curM.maxVxodi = curM.maxEx * 5;
            curM.SosdatObekti(kolObektovMira);
            curM.SosdatSlu4Svasi();

            DrawWorld dw = new DrawWorld(curM, gr);

            //gr.DrawLine(new Pen(Color.DarkBlue, 1), 10, 10, 400, 10);
            //gr.DrawLine(new Pen(Color.DarkBlue, 1), 10, 12, 400, 12);
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }




    sealed public class constants
    {
        public Dictionary<int, int> compability;
        public Random randObj;                     //случайный объект
        private int[] vero9t1; //массив Ид типов оперов
        private int[] vero9t2; //массив вероятностей типов оперов
        private int[] vero9t3; //массив пределов попадания вероятности
        private int maxNumb;  //верхний предел от суммы всех элементов
        public int[] OpisTipov;      //таблица описывающая кол входов типов
        public int[][] opisVx; //описание типов входов оперов
        public int[] vixodiOperov;
        //-----------------------------------------------------
        public const int kolVxodov = 11; //кол внешних входов 11
        public const int kolVixodov = 1; //кол внешних выходов 1
        //----------------------------------------------------

        public constants()
        {
            randObj = new Random();
            OpisTipov = new int[22] { 0, 3, 3, 3, 3, 3, 2, 4, 1, 2, 3, 3, 1, 3, 2, 2, 2, 2, 3, 1, 1, 2 }; //кол входов
            //OpisTipov = new int[20] { 0, 1 ,2, 3, 4, 5, 6, 7, 8, 9, 10,11,12,13,14,15,16,17,18,19,20,21}; //номера операторов
            vero9t1 = new int[20];
            vero9t2 = new int[20];
            vero9t3 = new int[20];
            #region vero9t-Add
            for (int i = 0; i < 20; i++) //назначаем индексы
                vero9t1[i] = i;

            vero9t2[1] = 100;
            vero9t2[2] = 70;
            vero9t2[3] = 30;
            vero9t2[4] = 30;
            vero9t2[5] = 30;
            vero9t2[6] = 30;
            vero9t2[7] = 80;
            vero9t2[8] = 30;
            vero9t2[9] = 30;
            vero9t2[10] = 30;
            vero9t2[11] = 30;
            vero9t2[12] = 30;
            vero9t2[13] = 30;
            vero9t2[14] = 30;
            vero9t2[15] = 30;
            vero9t2[16] = 30;
            vero9t2[17] = 30;
            vero9t2[18] = 30;
            vero9t2[19] = 30;
            #endregion

            Array.Sort(vero9t2, vero9t1); //отсортировали по возрастанию вероятностей
            // vero9t3[0] = vero9t2[0];
            for (int i = 1; i <= vero9t2.GetUpperBound(0); i++) //делаем разбивку
                vero9t3[i] = vero9t2[i] + vero9t3[i - 1];

            maxNumb = vero9t3[vero9t3.GetUpperBound(0)]; //верхний предел от суммы всех элементов
            compability = new Dictionary<int, int>();
            #region compability-Add
            compability.Add(12, 20);//Число (1),Бул (2),Тип оператора (3),Эземпляр оператора (4),Контакт (5),ЛюбойТип (6)
            compability.Add(13, 20); //первое число-выход. второе-вход
            compability.Add(14, 20);
            compability.Add(15, 30);
            compability.Add(16, 100);
            compability.Add(21, 40);
            compability.Add(22, 100);
            compability.Add(23, 0);
            compability.Add(24, 0);
            compability.Add(25, 0);
            compability.Add(26, 100);
            compability.Add(31, 30);
            compability.Add(32, 0);
            compability.Add(33, 100);
            compability.Add(34, 0);
            compability.Add(35, 0);
            compability.Add(36, 100);
            compability.Add(41, 30);
            compability.Add(42, 0);
            compability.Add(43, 0);
            compability.Add(44, 100);
            compability.Add(45, 0);
            compability.Add(46, 100);
            compability.Add(51, 30);
            compability.Add(52, 0);
            compability.Add(53, 0);
            compability.Add(54, 0);
            compability.Add(55, 100);
            compability.Add(56, 100);
            compability.Add(61, 100);
            compability.Add(62, 100);
            compability.Add(63, 100);
            compability.Add(64, 100);
            compability.Add(65, 100);
            compability.Add(66, 100);
            #endregion
            #region opisVx-Add
            opisVx = new int[22][];
            //Число (1),Бул (2),Тип оператора (3),Эземпляр оператора (4),Контакт (5),ЛюбойТип (6), Никакой (7)
            opisVx[1] = new int[3] { 2, 1, 1 };
            opisVx[2] = new int[3] { 2, 1, 1 };
            opisVx[3] = new int[3] { 2, 1, 1 };
            opisVx[4] = new int[3] { 2, 1, 1 };
            opisVx[5] = new int[3] { 2, 1, 1 };
            opisVx[6] = new int[2] { 2, 1 };
            opisVx[7] = new int[4] { 2, 1, 1, 1 };
            opisVx[8] = new int[1] { 2 };
            opisVx[9] = new int[2] { 2, 1 };
            opisVx[10] = new int[3] { 2, 4, 1 };
            opisVx[11] = new int[3] { 2, 5, 4 };
            opisVx[12] = new int[1] { 2 };
            opisVx[13] = new int[3] { 2, 5, 4 };
            opisVx[14] = new int[2] { 2, 5 };
            opisVx[15] = new int[2] { 2, 4 };
            opisVx[16] = new int[2] { 2, 3 };
            opisVx[17] = new int[2] { 2, 6 };
            opisVx[18] = new int[3] { 2, 4, 1 };
            opisVx[19] = new int[1] { 2 };
            opisVx[20] = new int[1] { 2 };
            opisVx[21] = new int[2] { 2, 1 };

            vixodiOperov = new int[22] { 0, 1, 1, 1, 1, 1, 1, 2, 1, 1, 5, 2, 7, 7, 4, 3, 4, 4, 5, 2, 1, 7 }; //7 - любой вх
            #endregion


        }
        public int vibratSlu4Oper() //выбирает случ опер в соответствии с вероятностями
        {
            int kolInterval;
            int resNum = randObj.Next(maxNumb); //случайное число от 0 до макс

            for (int i = vero9t2.GetUpperBound(0) - 1; i >= 0; i--) //делаем разбивку //-1 потому что начинаем не с края, а со след после края элемента
            {
                if (vero9t3[i] <= resNum) //попадает ли в текущии предел
                    return (vero9t1[i + 1]); //+1 из-за того что мы берем интервал вниз
                else
                {
                    kolInterval = (vero9t3[i] - resNum) / vero9t2[i]; // на сколько минимум нам нужно переместиться вперед
                    if (kolInterval > 1)
                        i = i - kolInterval + 1;// плюс 1 из-за i--
                }

                //if (i == 0)
                //    return vero9t1[1];

            }
            return 1;
        } //выбриает случайный опер в соответствии с вероятностями  существования оперов и возвращает его тип






    }

    sealed class Mir //здесь содержится структура каждого мира
    {
        public int[] TipEks;          //таблица описывающая типы экземпляров
        public int[] OpisTipov;      //таблица описывающая кол входов типов
        //  public int   [,] Vxodi;         //таблица описывающая входы
        public int[] Fcontacts;    //таблица описывающая первые контакты
        public int[,] Kanali;      //2-х мерный массив описывающий каналы. Массив избыточен так как есть массив ExVix соддержащий связь входа и выхода, но он нужен для увелечения производительности. Нужен для того, что бы не надо было искать все входы, которые соответствуют этому выходу
        public int[] poslKanali;  //массив называющий кол выходов объекта
        public int[] kolKvantov;          //часть таблицы входы с кол квантов
        public int[] ExVix;          //часть таблицы входы с экземлярами выхода
        public int[] ExVx;          //часть таблицы входы с экземляром входа
        public int lastEx; // Ид последнего экземпляра
        private int curRow;       //текущая строка в массиве каналы
        private System.Diagnostics.Stopwatch chasi;  //часы этого мира
        private Random randObj;                     //случайный объект
        private constants constant;
        private Ispit isp; //объект с испытаниями
        int lastK; //Ид последнего контакта 
        private int tekObekt;
        private int kolVxodov; //кол внешних входов 11
        private int kolVixodov; //кол внешних выходов
        public constants constantM;
        public int pravOtveti; //кол правильных ответов мира на задания
        public int nePravOtveti; //кол неправильных ответов мира на задания

        //--------------------------------------------------------------------------
        public int maxVxodi = 5000; //максимально возможное колличесвтво входов
        public int maxEx = 1100; //максимально возможное колличесвтво оперов
        public int maxVix = 7; //максимально возможное выходов у одного опера
        public int existProd = 20; //для какой части оперов подключать вход существования к выходу, от ста процентов
        //----------------------------------------------------------------------------


        public Mir(constants constant)
        {
            constantM = constant;
            kolVixodov = constants.kolVixodov;
            kolVxodov = constants.kolVxodov;
            pravOtveti = 0;
            nePravOtveti = 0;
            lastK = 0;
            chasi = new System.Diagnostics.Stopwatch();//забацали новые часы
            TipEks = new int[maxEx];
            OpisTipov = constant.OpisTipov;
            kolKvantov = new int[maxVxodi];
            ExVix = new int[maxVxodi];
            ExVx = new int[maxVxodi];
            Fcontacts = new int[maxEx];
            Kanali = new int[maxEx, maxVix];
            poslKanali = new int[maxEx];
            randObj = new Random();
            this.constant = constant;
            isp = new Ispit(); //спецом наоборот. входы и выходы внешнего и этого мира не совпадают
            for (int i = 0; i < kolVxodov; i++) //добавляем объекты внешние входы
                SosdatEx(20);
            for (int i = 0; i < kolVixodov; i++) //добавляем объекты внешние выходы
                SosdatEx(21);
            //        isp.curIsp = 8;
            //        isp.newSeria();
            //        isp.ispTime = 500;
            //        isp.kolOp = 2;
            //        isp.startIsp();


            //// debuuug
            //int ob = SosdatEx(18); //создаем опер
            //SosdatEx(1); //создаем опер
            //SosdatKanal(6, 1);// первый вход и источник
            //SosdatKanal(7, 2);// первый вход и источник
            //SosdatKanal(4, 4);// первый вход и источник

            //SosdatKanal(9, 1);// первый вход и источник
            //obrob();
            //obrob();
            //lastK = lastK;
            // debuuug


        }
        public void Obrob()
        {
            int res;//результат операции
            chasi.Start();
            curRow = 1; //нулевая строка не обрабатывается спецом из-за ластЭкс


            do //пошли переберать все строки таблицы
            {
                tekObekt = ExVx[curRow]; //текущий обробатываемый объект
                if (kolKvantov[curRow] == 1) //Если у оператора флаг несуществования,пропускаем его.
                {
                    res = ExVx[curRow]; //Ид несуществующего экземпляра
                    res = TipEks[res]; //тип экземпляра
                    res = OpisTipov[res]; //кол входов этого типа экземпляра
                    curRow = curRow + res; //перемещаем строку с учетом тек перемещения на след объект
                }
                else
                    curRow++;

                ObrobOper(TipOpera()); //выбираем что делать по текущему типу эземпляра
            } while (curRow <= lastK);

            chasi.Stop();//остановили часы мира
        }
        private void UstVis(int Ex, int porVix, int value)
        {
            int res = Fcontacts[Ex];
            int kont = res + porVix;
            kolKvantov[kont] = value;
        }
        private void ObrobOper(int oper)
        {
            int res, res2;//результат операции
            //try
            //{
            switch (oper) //выбираем что делать по текущему типу эземпляра
            {
                case 1: //оператор плюс
                    res = SnachVxoda() + SnachVxoda();
                    if (res > 0)
                        SapisatVixod(res);
                    break;
                case 2: //минус
                    res = SnachVxoda();
                    res2 = SnachVxoda();
                    if (res > res2)
                    {
                        res = res - res2;
                        SapisatVixod(res);
                    }
                    break;
                case 3: //*
                    res = SnachVxoda() * SnachVxoda();
                    if (res > 0)
                        SapisatVixod(res);
                    break;
                case 4: //делить
                    res = SnachVxoda();
                    res2 = SnachVxoda();
                    if (res2 != 0)
                    {
                        res = res / res2;
                    }
                    SapisatVixod(res);
                    break;
                case 5: //^
                    res = SnachVxoda();
                    res2 = SnachVxoda();
                    res = (int)Math.Pow(res, res2);
                    if (res > 0)
                        SapisatVixod(res);
                    break;
                case 6: //=
                    SapisatVixod(SnachVxoda());
                    break;
                case 7: //если
                    res = SnachVxoda();
                    if ((res > SnachVxoda()) && (res < SnachVxoda()))
                        SapisatVixod(1);
                    else
                        SapisatVixod(0);
                    break;
                case 8: //ТекущееВремя
                    res = (int)chasi.ElapsedMilliseconds;
                    SapisatVixod(res);
                    break;
                case 9: //СлучайноеЧисло
                    res = randObj.Next(SnachVxoda()); //генеруруем случ число от нуля до первого входа
                    SapisatVixod(res);
                    break;
                case 10: //ПолучитьИдКонтакта
                    res2 = SnachVxoda();
                    if (res2 < maxEx)
                    {
                        res = Fcontacts[res2];
                        if (res > 0)
                        {
                            res2 = res + SnachVxoda();//Первый контакт плюс порядковый номер контакта
                            if ((res2 < maxEx) && (res < maxEx))
                            {
                                if (ExVx[res] == ExVx[res2]) //если входящий объект соответствует контаку - пишем
                                    SapisatVixod(res2);
                            }
                        }
                    }
                    break;
                case 11: //СуществуетЛиКанал
                    res = SnachVxoda();
                    res2 = SnachVxoda();
                    if (res < maxVxodi && ExVix[res] == res2)
                        SapisatVixod(1);
                    break;
                case 12: //УдалитьКанал
                    res = SnachVxoda(); //ИдКанала
                    if (res < maxVxodi)
                        ExVix[res] = 0;
                    break;
                case 13: //СоздатьКанал
                    SosdatKanal(SnachVxoda(), SnachVxoda());
                    break;
                case 14: //ПолучитьЭкземплярИзКонтакта
                    res = SnachVxoda();
                    if (res < maxVxodi)
                    {
                        res = ExVx[res]; //ИдЭкземпляра
                        SapisatVixod(res);
                    }
                    break;
                case 15: //ПолучитьТипЭкземпляра
                    res = SnachVxoda();
                    if (res < maxEx)
                    {
                        res = TipEks[res]; //ТипЭкземпляра
                        SapisatVixod(res);
                    }
                    break;
                case 16: //СоздатьЭкземпляр
                    res = SnachVxoda();
                    if ((res > 0) && (res < 20))
                        SapisatVixod(SosdatEx(res));
                    break;
                case 17: //ПолучитьСсылкуНаЭтотЭкземпляр
                    res = ExVix[curRow]; //Экземпляра от которого с выхода поступает инфа на второй вход
                    // curRow++; //переместили строку т.к. не пользовались считыванием со входа
                    SapisatVixod(res);
                    break;
                case 18: //ПолучитьВходИзВыхода
                    res = SnachVxoda(); //ИдЭкземпляра
                    res2 = SnachVxoda(); //ПорядНомерВхода
                    if ((res2 < maxVix) && (res < maxEx))
                    {
                        res = Kanali[res, res2];
                        SapisatVixod(res);
                    }
                    break;
                case 19: //всегда возвращает еденицу
                    SapisatVixod(1);
                    break;
                case 20: //объект - потусторонний выход. Все входы идут сначала
                    //Kanali[tekObekt,0]=isp.voprosi[tekObekt]; //записали с вопросов значение выхода потустороннего объекта
                    SapisatVixod(isp.voprosi[tekObekt - 1]); //записали на выхи значение тек объекта
                    break;
                case 21: //объект - потусторонний вход
                    res = SnachVxoda(); //входящее значение
                    isp.otveti[tekObekt - kolVxodov - 1] = res; //передаем инфу во вне
                    break;


            }

            //}
            //catch (IndexOutOfRangeException) { }


        } //выбираем что делать по текущему типу эземпляра
        private int SnachVxoda() //находит значение для этого входа. При каждом вызове значение текущей строки увеличивается на еденицу
        {
            int vixod = kolKvantov[curRow];//выход текущего контакта
            kolKvantov[curRow] = 0; //ОБНУЛИЛИ считаный вход
            curRow++;
            return vixod;
        }
        private int TipOpera() //находит тип этого оператора
        {
            return TipEks[tekObekt];
        }
        private void SapisatVixod(int vixod) //записывает выход
        {
            // int curOb=Vxodi[curRow-1,0]; //текущий объект для которого записуем выход (вернулись назад т.к. чтение выхода двигает вперед)
            int curV;
            for (int i = 0; i < poslKanali[tekObekt]; i++)
            {
                curV = Kanali[tekObekt, i]; //текущий контакт
                kolKvantov[curV] = vixod;
            }
        }
        public void SosdatObekti(int kolObektov)
        {
            for (int i = 0; i < kolObektov; i++)
                SosdatEx(constant.vibratSlu4Oper());
        }
        private int SosdatEx(int tipOpera) //создаёт экземпляр оператора
        {
            if (lastEx == maxEx) //превышена верхняя граница массива
                return 0;

            lastEx++; //Ид нового экземпляра
            TipEks[lastEx] = tipOpera; // установили тип опера
            int kolVxodov = OpisTipov[tipOpera];// кол входов
            lastK++;
            Fcontacts[lastEx] = lastK;
            int kont;
            for (kont = lastK; kont < kolVxodov + lastK; kont++)
                ExVx[kont] = lastEx; //установили объект

            lastK = kont - 1;
            return lastEx;
        }
        private void SosdatKanal(int vx, int Ex2)  //Ид вход контакта вход, объект выход
        {
            if ((Ex2 != 0) && (Ex2 < maxEx)) //с нулевым не соеденяем- это ошибка
            {
                int poslK = poslKanali[Ex2]; //последний контакт для этого объекта
                if (poslK != maxVix)
                {
                    Kanali[Ex2, poslK] = vx; //установили новый вход в каналах, до ++ потому, что в посл контакты -количество, а тут порядковый номер, т.е. -1
                    ExVix[vx] = Ex2; //добавили Ид экземпляра выхода еще и в таблицу контакты  
                    poslK++;
                    poslKanali[Ex2] = poslK;
                }
            }
        }
        public void SosdatSlu4Svasi()
        {
            int curV;
            int lastEx2 = lastEx;
            int delta;
            int vxOper, celOper;
            int tipVx, tipVix;
            int porK; //порядковый номер контакта
            int comp;
            int sum;
            int comSl;

            for (int i = 1; i <= lastK; i++)
            {
            firstL:
                curV = randObj.Next(1, lastEx2); //опер с выходом которого мы соеденим этот вход
                if (poslKanali[curV] == maxVix)
                    goto firstL;

                delta = randObj.Next(-1, 1); //направление перемещения при несовпадении или привышении допустимого кол выходов
            startL:
                while (poslKanali[curV] >= maxVix) //пока превышена макс кол выходов - двигаемся
                    MoveCurV(ref curV, delta);

                vxOper = TipEks[ExVx[i]];
                porK = i - Fcontacts[ExVx[i]];

                if (porK == 0) //первый вход существования
                {
                    comSl = randObj.Next(100);
                    if (existProd >= comSl) //непопали
                        continue; //значит переходим на след вход
                }

                celOper = TipEks[curV];
                tipVx = constant.opisVx[vxOper][porK];
                tipVix = constant.vixodiOperov[celOper]; //было celOper-1 т.к. начало с нуля а не с 1

                if (tipVx == tipVix || tipVx == 6 || tipVix == 7) // Если тип - Любой вход или любой выход или типы входа и выхода совпадают - тогда в любом случае создаем канал
                    SosdatKanal(i, curV);
                else
                {

                    sum = tipVx * 10 + tipVix;
                    comp = constant.compability[sum];

                    if (comp == 100)
                        SosdatKanal(i, curV);
                    else
                    {
                        comSl = randObj.Next(100);
                        if (comp <= comSl) //попали
                            SosdatKanal(i, curV);
                        else
                        {
                            MoveCurV(ref curV, delta);//перемещаем выход и начинаем заново
                            goto startL;
                        }
                    }
                }
            }
        }
        private void MoveCurV(ref int curV, int delta) //перемещает текущий выход в сторону дельта
        {
            curV = curV + delta;

            if (curV == 0) //дошли до низа
                curV = lastEx;

            if (curV > lastEx) //дошли до верха
                curV = 1;
        }

    }

    sealed class Ispit //класс который генерирует испытания
    {

        public int[] otveti; //входы с ответной инфой этого класса
        public int[] voprosi; //выходы с вопросами этого класса
        private int kolVxodov; //кол входов
        private int kolVixodov; //кол выходов с вопросами
        private Random randObj;
        //public static Timer provTimer,ispTimer;
        private int firstOp;
        private int res; //количество влияющих на результат объектов
        private int res2;
        private int[] slovoPos;//тут содержатся порядковые номера нейронов содержащих слово
        private int curPosInSlPos;
        private int[] slovo;//тут содержется значение самого слова
        private int curDl;//длина тек сегмента 
        private int curPos; //тек позиция начала сегмента слова

        public static Mir mir;
        private double koef1, koef2, pow1, pow2; //для степенной функции
        //-------------------------------------------
        private const int maxPow = 6; //максимально вохможная степень
        private const int maxKoef = 10; //максимально вохможный коэф
        public int MaxDlinaSegmenta = 4; //длина фразы функции слово
        public int kolSegmentov = 3; //кол фраз
        public int MaxVal = 2; //максимальное значение в масиве вопросы(не влючаемое)
        // public int provTime=1; //кол милесекунд за которые должен быть дан ответ, или обудет защитан проигрышь
        //  public int ispTime=10; //кол милесекунд через которые будет новое испытание
        public int kolOp = 2; //количество влияющих на результат объектов
        public int curIsp = 1; //тип текущего испытания
        //---------------------------------------------------





        public Ispit()
        {
            this.kolVixodov = constants.kolVxodov;
            this.kolVxodov = constants.kolVixodov;// спецом наоборот т.к. вход мира - это выход испытаний
            voprosi = new int[kolVixodov];
            otveti = new int[kolVxodov];
            randObj = new Random();    //случайный объект
            slovoPos = new int[kolVixodov];
            slovo = new int[kolVixodov];
            //provTimer = new Timer(provTime);
            //provTimer.Elapsed += new ElapsedEventHandler(nastaloVrem9Prov);
            //ispTimer = new Timer(ispTime);
            //ispTimer.Elapsed += new ElapsedEventHandler(nastaloVrem9Prov);
        }
        public void NewSeria() //новая серия испытаний
        {
            switch (curIsp)
            {
                default:
                    firstOp = randObj.Next(2, kolVixodov); //первый сравниваемый объект(выбирает новые плоложения операторов)
                    break;
                case 7: //степенная
                    GenPowF();
                    break;
                case 8: //слово
                    ChoseWordTipe();
                    break;
            }
        }
        public void StartIsp() //провести очередное испытание в серии
        {
            voprosi[0] = curIsp;
            FillVoprRnd(); //заполнили новыми вопросам
            // provTimer.Start();
            // ispTimer.Start();
        }
        private void FillVoprRnd() //заполняет случайными значениями массив вопросы до макс вал
        {
            for (int i = 2; i < kolVixodov; i++) //со второго потому что первые два: тип испытания и результат
                voprosi[i] = randObj.Next(MaxVal);
        }
        // private void nastaloVrem9Prov(object source, ElapsedEventArgs e) //настало время проверки ответа
        public void NastaloVrem9Prov() //настало время проверки ответа
        {
            //provTimer.Stop();

            res = voprosi[firstOp];
            if (kolOp == 1)
                res = Oper(res, 0);
            else
            {
                for (int i = 1; i < kolOp; i++)
                {
                    if ((i + firstOp) >= kolVixodov) //если вышли за край -начинаем сначала
                        res = Oper(res, voprosi[i + firstOp - kolVixodov + 1]); //+1 -первый Эелемент мас
                    else
                        res = Oper(res, voprosi[i + firstOp]);
                }
            }
            if (otveti[0] == res)
            {
                mir.pravOtveti++;
                voprosi[1] = 1; //результат выполнения для нейрона
            }
            else
            {
                mir.nePravOtveti++;
                voprosi[1] = 0;
            }

        }
        //private void nastaloVrem9NovIsp(object source, ElapsedEventArgs e) //настало время нового испытания в серии
        //{
        //    startIsp();
        //}
        private void ChoseWordTipe() //выбирает тип использованного слова
        {
            curPosInSlPos = 0;
            curPos = 1;//кроме нулевого входа, он показывает результат испытаний
            // pos = kolVixodov / MaxDlinaSegmenta;
            for (int i = 0; i < kolSegmentov; i++)
            {
                curDl = randObj.Next(MaxDlinaSegmenta);
                curPos = randObj.Next(curPos, curPos + MaxDlinaSegmenta);

                if (curPos >= kolVixodov) //зашли за окончание
                    return;

                for (int i2 = 0; i2 < curDl; i2++)
                {

                    slovoPos[curPosInSlPos] = (curPos);
                    curPosInSlPos++;
                    curPos++;

                }

            }

        }
        private int IsWordInWopr() //проверяет есть ли сохраненное слово в вопросах или нет
        {
            for (int i = 0; slovoPos[i] != 0; i++)
            {
                if (slovo[i] != voprosi[slovoPos[i]])
                    return 0;
            }
            return 1;
        }
        private void GenPowF() //генерируем коэфы степенной функции
        {
            pow1 = randObj.Next(maxPow) + randObj.NextDouble();
            pow2 = randObj.Next(maxPow) + randObj.NextDouble();
            koef1 = randObj.Next(maxKoef) + randObj.NextDouble();
            koef2 = randObj.Next(maxKoef) + randObj.NextDouble();
        }
        private int Oper(int one, int two)
        {
            switch (curIsp)
            {
                case 1: //лог И, то же что и умножение для 0  - 1
                    return (one * two);
                case 2://лог ИЛИ, то же что и сумма для 0  - 1
                    return (one + two);
                case 3://исключающее  ИЛИ
                    res2 = one + two;
                    if (res2 == 2)
                        return 0;
                    else
                        return res2;
                case 4://НЕ
                    if (one == 1)
                        return 0;
                    else
                        return 1;
                case 5://ИЛИ-НЕ
                    one = one + two;
                    goto case 4;
                case 6://И-НЕ
                    one = one * two;
                    goto case 4;
                case 7://степенная функция
                    return (int)(koef1 * Math.Pow(one, pow1) + koef2 * Math.Pow(two, pow2));
                case 8://функция Слово
                    return IsWordInWopr();
            }
            return 0;

        }

    }
    sealed class Wrap //класс управляющая оболочка
    {
        public SortedList<Double, Mir> Miri = new SortedList<Double, Mir>(); //список с мирами и их эффективностями
        private Mir curM;
        private Ispit isp;
        private constants con;
        private int kolObektovMira;//текущее кол объектов мира
        //private int kolOtbirMirov;//кол отбираемых неудачных миров
        private int kolMirov;//кол поддреживаемых миров
        private int kolIspVSerii;//кол испытаний в 1 серии
        private int kolIspitaniiVserii; //кол испытаний в серии
        private int kolSerii = 5; //кол серий каждого типа игры. Каждый мир будет проходить этот тип испытаний только 1 раз
        private int kolObrobMiraVisp = 5; //сколько раз обработать мир до того как проверить ответ
        //   private const int kolIspitanii1etapa = 10000; //общее кол испытаний первого этапа отбора 
        private int kolCiklovEtapa; //общее кол циклов всех испытаний тек этапа отбора 
        private int kolTipovIspitanii = 8; //кол типов испытаний начиная с нижней границы 1      
        private int curMindex = 0;// тек проверяемый мир
        private int curEtap;// тек этап

        //debug----------------
        private Stopwatch sw;
        private int kol = 0;
        private int[] time;

        public Wrap()
        {
            con = new constants();
            isp = new Ispit();
            curMindex = 0;
        }

        public void Na4AtOtbor()
        {
            time = new int[5];
            sw = new Stopwatch();
            // kolOtbirMirov = 200;
            kolObektovMira = 15;
            isp.curIsp = 1;
            isp.kolOp = 2;

            kolMirov = 50;
            curEtap = 1;
            kolCiklovEtapa = 50000;
            kolTipovIspitanii = 1;
            kolSerii = 20;
            kolIspitaniiVserii = 50;
            kolObrobMiraVisp = 5;
            //dobavitNoviiMir();
            //sw.Start();
            //for (int i = 0; i < 10000; i++)
            //TestMir();
            //sw.Stop();
            //Console.WriteLine(sw.ElapsedMilliseconds);

            NextEtap();



            //Console.WriteLine(miri.Keys[curMindex - 1]);
            // Console.ReadLine();
            //  dobavitMiri(100);
            // TestPoIspitaniu();




        }

        private void NextEtap()
        {
            for (int i0 = 0; i0 < kolCiklovEtapa; i0++) //пошел первый этап
            {
                for (int i = 1; i <= kolTipovIspitanii; i++)
                {
                    isp.curIsp = kolTipovIspitanii;
                    TestPoTipuIgri();// одинаковые параметры для всех типов игр
                }
            }
        }

        private void TestPoTipuIgri() //добавляет новый мир, проводит испытание по этому типу игры и записует результат(эффективность) в массив миры
        {
            double efect = curM.pravOtveti / (curM.pravOtveti + curM.nePravOtveti);

            kol++;// для дебага
            //   sw.Start();
            DobavitNoviiMir();
            //sw.Stop();
            //time[0] = (time[0] + (int) sw.ElapsedMilliseconds) / 2;
            //Console.WriteLine(sw.ElapsedMilliseconds.ToString() + " добавить мир");
            //sw.Reset();
            //sw.Start();
            TestMir();
            //sw.Stop();
            //Console.WriteLine(sw.ElapsedMilliseconds.ToString() + " тест мира мир");
            if (curMindex == kolMirov) //если тек мир подошол к границе - удаляем часть списка перемещаем индекс назад
            {
                curMindex--;
                Miri.RemoveAt(0);
            }

            if (curM.pravOtveti > 0)
            {
                if (Miri.ContainsKey(efect))
                    Miri.Add((efect + con.randObj.NextDouble()), curM);
                else
                    Miri.Add(efect, curM);

                curMindex++;
            }
        }
        private void TestMir() //тестирует текущий мир в curM по текущему виду испытаний kolSerii новых серий(новые местоположения аргуметов) по kolIspitaniiVserii испытаний в каждой серии 
        {
            Ispit.mir = curM;
            for (int i0 = 0; i0 < kolSerii; i0++)
            {
                isp.NewSeria();
                for (int i = 0; i < kolIspitaniiVserii; i++)
                {
                    isp.StartIsp();
                    for (int i2 = 0; i2 < kolObrobMiraVisp; i2++)
                    {
                        curM.Obrob();
                    }
                    isp.NastaloVrem9Prov();
                }
            }
        }
        private void DobavitNoviiMir() //добавляет новый мир
        {
            switch (curEtap)
            {
                case 1://добавляет новый мир и записывает ссылку на него в curM
                    curM = new Mir(con);
                    curM.maxEx = kolObektovMira * 3;//??????
                    curM.maxVxodi = curM.maxEx * 5;
                    curM.SosdatObekti(kolObektovMira);
                    curM.SosdatSlu4Svasi();
                    break;
                case 2:
                    curM = Miri.Values[con.randObj.Next(curMindex)];//добавляет новый мир копией случайного мира от 0 до curMindex
                    break;

            }

        }
    }


    sealed class Test //для тестирования производительности
    {
        private long kolRas = 50000;
        private const int kolObektovMira = 15;
        private Mir curM;
        private Ispit isp;
        private constants con;
        private Stopwatch sw;
        public long testSosdatObL;
        public long testSosdatSv9siL;
        public long obrobMirL;
        public long startIspL;
        public long nastaloVrrm9ProvL;


        public Test()
        {
            con = new constants();
            isp = new Ispit();
            sw = new Stopwatch();
            Ispit.mir = curM;

        }

        public void StartTest()
        {
            TestSosdatOb();
            TestSosdatSv9Si();
            StartIsp();
            NastaloVrrm9Prov();
            ObrobMir();
            Console.WriteLine(nastaloVrrm9ProvL + " nastaloVrrm9ProvL");
            Console.WriteLine(startIspL + " startIspL");
            Console.WriteLine(obrobMirL + " obrobMirL");
            Console.WriteLine(testSosdatSv9siL + " testSosdatSv9siL");
            Console.WriteLine(testSosdatObL + " testSosdatObL");
        }

        public void TestSosdatOb()
        {
            sw.Reset();
            sw.Start();
            for (int i = 0; i < kolRas; i++)
            {
                curM = new Mir(con);
                curM.maxEx = kolObektovMira * 3;//??????
                curM.maxVxodi = curM.maxEx * 5;
                curM.SosdatObekti(kolObektovMira);
            }
            sw.Stop();
            testSosdatObL = sw.ElapsedTicks / kolRas;
        }
        public void TestSosdatSv9Si()
        {
            sw.Reset();
            sw.Start();
            for (int i = 0; i < kolRas; i++)
            {
                curM = new Mir(con);
                curM.maxEx = kolObektovMira * 3;//??????
                curM.maxVxodi = curM.maxEx * 5;
                curM.SosdatObekti(kolObektovMira);
                curM.SosdatSlu4Svasi();

            }
            sw.Stop();
            testSosdatSv9siL = ((sw.ElapsedTicks - testSosdatObL) / kolRas);
            Ispit.mir = curM;
        }
        public void ObrobMir()
        {
            sw.Reset();
            sw.Start();
            for (int i = 0; i < kolRas; i++)
                curM.Obrob();
            sw.Stop();
            obrobMirL = (sw.ElapsedTicks / kolRas);
        }
        public void StartIsp()
        {
            sw.Reset();
            sw.Start();
            for (int i = 0; i < kolRas; i++)
                isp.StartIsp();
            sw.Stop();
            startIspL = (sw.ElapsedTicks / kolRas);
        }
        public void NastaloVrrm9Prov()
        {
            sw.Reset();
            sw.Start();
            for (int i = 0; i < kolRas; i++)
                isp.NastaloVrem9Prov();
            sw.Stop();
            nastaloVrrm9ProvL = (sw.ElapsedTicks / kolRas);
        }

    }


    sealed class DrawWorld // класс отрисовки мира
    {
        private Mir curM;
        private const int radiusO = 30; // радиус объекта
        Graphics gr;
        Point startP = new Point(30, 30); // верхний левый угол откуда будут рисоваться объекты мира
        Point curP; // текущая точка отрисовки очередного объекта

        public DrawWorld(Mir mir, Graphics graf)
        {
            int y = 1; // условные координаты местоположения объекта
            int x = 1;
            gr = graf;
            curM = mir;
            curP = startP;
            int dlinaGrani = Convert.ToInt32(Math.Sqrt(mir.lastEx)); // длинна вертикальной грани(и горизонтальной, если получится равнобедренный квадрат)
            int sdvigGryas = (dlinaGrani + 1) * 2; // расстояние между объектами. задается таким образом, что бы можно было соеденить связями все объекты большей грани, так что бы между ними был хотя бы пиксель промежутка      
            int sdvig = sdvigGryas + radiusO; // общий чистый сдвиг с учетом радиуса объекта
            // Create font and brush for objects
            Font obFont = new Font("Arial", 16);
            SolidBrush obBrush = new SolidBrush(Color.Black);



            for (int co = 0; co <= mir.lastEx; co++)
            {


                if (y > dlinaGrani) // если исчерпали лимит пересечения по вертикали - перемещаемся по горизонтали
                {
                    y = 1;
                    x = x + sdvig;
                }

                curP.X = startP.X + x;
                curP.Y = startP.Y + y;

                gr.DrawEllipse(new Pen(Color.DarkBlue, 2), curP.X, curP.Y, radiusO * 2, radiusO * 2);
                gr.DrawString(co.ToString(), obFont, obBrush, curP.X, curP.Y);

                y = y + sdvig;
            }

        }

        private void DrawOb(int cOb) // рисует очередной объект мира
        {
            int ctip = curM.TipEks[cOb];

        }

    }
}
