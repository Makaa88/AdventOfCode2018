using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Day4
{
    class Program
    {
        static void Main(string[] args)
        {
            var lines = File.ReadAllLines("dane.dat");
            SortedSet<string> set = new SortedSet<string>();
            SortedSet<Guard> guard = new SortedSet<Guard>();

            int idNumber = -1;
           foreach(string line in lines)
            {
                set.Add(line);
                if(line.Contains("#"))
                {
                    string[] s = line.Split('#', ' ');
                    idNumber = int.Parse(s[4]);
                    guard.Add(new Guard(idNumber));
                }
            }
            
           foreach(string line in set)
            {

                if (line.Contains("#"))
                {
                    string[] s = line.Split('#', ' ');
                    idNumber = int.Parse(s[4]);
                    FindGaurd(guard, idNumber).AddWatch(line);
                    
                }
                else
                {
                    FindGaurd(guard, idNumber).MakeAChange(line);
                }
            }
            int max = 0;
            int id = -1;
            int asleep = -1;
            int idmost = -1;
            int valuemost = -1;
            int asleepmost = -1;
           foreach(Guard g in guard)
            {
                if(g.AmmountOfMinutesAsleep > max)
                {
                    id = g.ID;
                    max = g.AmmountOfMinutesAsleep;
                    asleep = g.MostMinutesAsleep;
                }
                if(valuemost < g.MostInrementValue)
                {
                    valuemost = g.MostInrementValue;
                    asleepmost = g.MostMinutesAsleep;
                    idmost = g.ID;
                }
            }
            Console.WriteLine("RESULT: {3},  MINUTES: {0}, ID: {1}, ASLEEP: {2}", max, id, asleep, id*asleep);
            Console.WriteLine("MOSTASLEEP: {0}, TIMES: {1},  RESULT: {2}", idmost, asleepmost, asleepmost*idmost);

            Console.ReadKey();
        }

     

        static Guard FindGaurd(SortedSet<Guard> guard, int idNumber)
        {
            foreach (Guard g in guard)
            {
                if (g.ID == idNumber && idNumber != -1)
                {
                    return g;
                }
            }
            return null;
        }
    }

   
    class Guard : IComparable<Guard>
    {
        public readonly int ID;
        public int AmmountOfMinutesAsleep = 0;
        public int MostMinutesAsleep = 0;
        public int MostInrementValue = -1;
        private int CurrentWatch = -1;
        List<Watch> Watches = new List<Watch>();
        private int[] minutes = new int [60];

        public Guard(int ID)
        {
            this.ID = ID;
            for (int i = 0; i < 60; i++)
                minutes[i] = 0;
        }

        public override string ToString()
        {
            return ID.ToString();
        }

        public int CompareTo(Guard guard)
        {
            if (this.ID > guard.ID) return -1;
            if (this.ID == guard.ID) return 0;
            return 1;
        }

        public void AddWatch(string line)
        {
            int[] time = GetHours(line);
            CurrentWatch++;
            Watches.Add(new Watch(time[0], time[1], time[2], time[3], time[4]));
        }
        
        private int[] GetHours(string line)
        {
            string[] s = line.Split('[', ']');
            string[] number = s[1].Split('-', ' ', ':');
            int[] time = new int[5];
            time[0] = int.Parse(number[0]);
            time[1] = int.Parse(number[1]);
            time[2] = int.Parse(number[2]);
            time[3] = int.Parse(number[3]);
            time[4] = int.Parse(number[4]);
            return time;
        }

        public void MakeAChange(string line)
        {
            string command = line.Split(']')[1];
            int[] time = GetHours(line);
            if(command == " falls asleep")
            {
                Watches.ElementAt(CurrentWatch).BeginSleep(time[4]);
            }
            else
            {
                int duration =  Watches.ElementAt(CurrentWatch).EndSleep(time[4]);
                AmmountOfMinutesAsleep += duration;
                for(int i = Watches.ElementAt(CurrentWatch).StartSleep; i < Watches.ElementAt(CurrentWatch).StopSleep; i++)
                {
                    minutes[i]++;
                    if (MostInrementValue < minutes[i])
                    {
                        MostMinutesAsleep = i;
                        MostInrementValue = minutes[i];
                    }
                }

            }
        }



    }

    class Watch
    {
        //Year of watch
        public int Year { get; set; }
        public int Month { get; set; } //month of watch
        public int Day { get; set; } //day of watch
        public int HourStart { get; set; }
        public int MinuteStart { get; set; }

        public int SleepTime { get; set; }
        public int AwakeTime { get; set; }

        public int MaxAmmountOfWatchSleep { get; set; }


        public int StartSleep { get; set; }
        public int StopSleep { get; set; }


        public Watch(int y, int m , int d, int hs, int ms)
        {
            this.Year = y;
            this.Month = m;
            this.Day = d;
            this.HourStart = hs;
            this.MinuteStart = ms;
        }

        public void BeginSleep(int minute)
        {
            StartSleep = minute;
        }

        public int EndSleep(int minute)
        {
            StopSleep = minute;
            if (StartSleep != -1) return StopSleep - StartSleep;
            return 0;
        }


       
    }
}
