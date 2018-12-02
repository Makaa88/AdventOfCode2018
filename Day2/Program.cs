using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Day2
{
    class Program
    {
        static void Main(string[] args)
        {
            int[] tab = { 0, 0 };
            string[] stringTab = new string[2];
            var lines = File.ReadAllLines("dane.dat");//string[]
            foreach(var line in lines)//string
            {
                bool two = true;
                bool three = true;
                foreach (char sign in line)
                {
                   int number = line.Count(f => f == sign);
                   if(number == 2 && two)
                    {
                        tab[0]++;
                        two = false;
                    }
                   else if(number == 3 && three)
                    {
                        tab[1]++;
                        three = false;
                    }
                }
            }
            Console.WriteLine("RESULT: {0}", tab[0]*tab[1]);
            bool flag = false;
            for(int i = 0; i < lines.Length-1; i++)
            {
                stringTab[0] = lines[i];
                string first = lines[i];
                for(int j = i+1; j < lines.Length; j++)
                {
                    int div = 0;
                    string temp = lines[j];
                    for(int k = 0; k < stringTab[0].Length; k++)
                    {
                        if (first[k] != temp[k]) div++;
                    }

                    if (div == 1)
                    {
                        stringTab[1] = lines[j];
                        flag = true;
                    }
                    
                }
                if (flag) break;
            }

            Console.WriteLine("RESULT: {0}", stringTab[0]);
            Console.WriteLine("RESULT: {0}", stringTab[1]);
            string t1 = stringTab[0];
            string t2 = stringTab[1];
            for(int i = 0; i < t1.Length; i++)
            {
                if (t1[i] == t2[i]) Console.Write("{0}", t1[i]);
            }


            Console.ReadKey();
        } 
    }
}
