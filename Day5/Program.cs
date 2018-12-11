using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Day5
{
    class Program
    {
        static void Main(string[] args)
        {
            var lines = File.ReadAllLines("dane.dat");
            string line = lines[0];
            Console.WriteLine(line.Length);

            /* while(React(ref line))
             {
                // Console.WriteLine(line.Length);
             }*/


            Dictionary<char, int> dic = new Dictionary<char, int>();
            for(int i = 0; i < line.Length; i++)
            {
                if(! dic.ContainsKey(char.ToUpper(line[i])))
                {
                    dic[char.ToUpper(line[i])] = RemoveAndReact(ref line, char.ToUpper(line[i]));
                }
            }
            int min = dic[char.ToUpper(line[0])];
            char sign = line[0];
            foreach(var e in dic)
            {
                if(e.Value < min)
                {
                    min = e.Value;
                    sign = e.Key;
                }
                Console.WriteLine(e.Key + ": " + e.Value);
            }


            Console.WriteLine("Result: {0}", line.Length);
            Console.WriteLine("Result2: {0} {1}",sign,min);
            Console.ReadKey();
        }


        static int RemoveAndReact(ref string line, char sign)
        {

            char[] str = new char[line.Length - Count(ref line, ref sign)];

            int j = 0;
            for(int i = 0; i < line.Length; i++)
            {
                if (line[i] == sign || line[i] == char.ToLower(sign))
                    continue;
                else
                {
                    str[j] = line[i];
                    j++;
                }
            }

            string strs = new string(str);
            while (React(ref strs))
            {

            }
            return strs.Length;
        }
        static bool React(ref string  line)
        {
            //Console.WriteLine(line);
            List<int> positions = new List<int>();
            bool isReact = false;
            for(int i  = 0; i < line.Length-1; i++)
            {
                if( (char.ToUpper(line[i]).Equals(char.ToUpper(line[i + 1]))) && (line[i].GetHashCode() != line[i+1].GetHashCode()) && !positions.Contains(i-1))
                {
                    positions.Add(i);
                    isReact = true;
                }
            }
            /*foreach(int p in positions)
            {
                Console.Write(p + " ");
            }*/
          // Console.WriteLine();
            char[] newString = new char[line.Length - 2*positions.Count];
            int currentPosition = 0;
            int j = 0;
           // Console.WriteLine("lenght = {0}, coutn = {1}, cahrsize = {2}",line.Length,positions.Count, line.Length - 2*positions.Count);
            if (isReact)
            {
                for (int i = 0; i < line.Length; i++)
                {
                   // Console.WriteLine("LOOP: i = {0}, cp = {1}", i, currentPosition); ;
                    if (currentPosition < positions.Count && i == positions[currentPosition] )
                    {
                        i++;
                        currentPosition++;
                    }
                    else
                        newString[j++] = line[i];
                }
                line = new string(newString);
            }
            //Console.WriteLine(line);
            return isReact;
        }

        static int Count(ref string line, ref char sign)
        {
            int result = 0;
            for(int i = 0; i < line.Length; i++)
            {
                if (line[i] == char.ToLower(sign) || line[i] == char.ToUpper(sign))
                    result++;
            }
            return result;
        }
    }
}
