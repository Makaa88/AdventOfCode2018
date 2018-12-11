using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Day3._1
{
    class Program
    {
        static void Main(string[] args)
        {
            var lines = File.ReadAllLines("dane.dat");
            int xmax = -1;
            int ymax = -1;
            int numberOfInches = 0;
            foreach(string line in lines)
            {
                var content = line.Split(' ');
                var firstPart = content[2].Split(',', ':');
                int leftEdgeDistance = int.Parse(firstPart[0]);
                int topEdgeDistance = int.Parse(firstPart[1]);
                var secondPart = content[3].Split('x');
                int x = int.Parse(secondPart[0]);
                int y = int.Parse(secondPart[1]);
                if (xmax < (leftEdgeDistance + x))
                    xmax = leftEdgeDistance + x;
                if (ymax < (topEdgeDistance + y))
                    ymax = topEdgeDistance + y;


            }

            int[,] table = new int[ymax, xmax];
            for (int i = 0; i < ymax; i++)
                for (int j = 0; j < xmax; j++)
                    table[i,j] = 0;

            Console.WriteLine("X: {0}, Y: {1}",xmax, ymax);

            foreach(string line in lines)
             {
                 var content = line.Split(' ');
                 var firstPart = content[2].Split(',', ':');
                 int leftEdgeDistance = int.Parse(firstPart[0]);
                 int topEdgeDistance = int.Parse(firstPart[1]);
                 var secondPart = content[3].Split('x');
                 int x = int.Parse(secondPart[0]);
                 int y = int.Parse(secondPart[1]);
                for(int i = leftEdgeDistance; i < leftEdgeDistance+x; i++)
                {
                    for(int j = topEdgeDistance; j < topEdgeDistance+y; j++)
                    {
                        table[j, i]++;
                        if (table[j, i] == 2)
                            numberOfInches++;
                    }
                }

             }
          
            string ID;

        

            foreach (string line in lines)
            {
                bool isAlone = true;
                var content = line.Split(' ');
                var firstPart = content[2].Split(',', ':');
                ID = content[0];
                int leftEdgeDistance = int.Parse(firstPart[0]);
                int topEdgeDistance = int.Parse(firstPart[1]);
                var secondPart = content[3].Split('x');
                int x = int.Parse(secondPart[0]);
                int y = int.Parse(secondPart[1]);
                for (int i = leftEdgeDistance; i < leftEdgeDistance + x; i++)
                {
                    for (int j = topEdgeDistance; j < topEdgeDistance + y; j++)
                    {
                        if (table[j, i] != 1)
                            isAlone = false;
                    }
                }
                if(isAlone)
                {
                    Console.WriteLine("Alone ID: {0}", ID);
                    break;
                }

            }


            Console.WriteLine("Inches: {0}", numberOfInches);

            Console.ReadKey();
        }
    }
}
