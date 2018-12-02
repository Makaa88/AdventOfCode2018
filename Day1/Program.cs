using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace Day1
{
    class Program
    {
        static void Main(string[] args)
        {
            int digit = 0;
            int sum = 0;
            var lines = System.IO.File.ReadAllLines("dane.dat");
            foreach(var line in lines)
            {
                sum += int.Parse(line);
            }
            Console.WriteLine("SUMA: {0}", sum);

            sum = 0;
            Dictionary<int, int> freq = new Dictionary<int, int>();
            freq.Add(sum, 1);
            bool flag = true;
            while(flag)
            {
                foreach(var line in lines)
                {
                    sum += int.Parse(line);
                    if(freq.ContainsKey(sum))
                    {
                        digit = sum;
                        flag = false;
                        break;
                    }
                    else
                    {
                        freq.Add(sum, 1);
                    }
                }
            }

            Console.WriteLine("FREQ: {0}", digit);
            Console.ReadLine();
        }
    }
}
