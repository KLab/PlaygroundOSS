/* 
   Copyright 2013 KLab Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
using System;
using EnginePrototype;

public class Program
{
    public static void start()
    {
        SampleGame.Program.start();
    }
}

namespace SampleGame
{
    public class Program
    {
        public static void start()
        {
            Main(null);
        }

        public static void Main(string[] args)
        {
            Console.WriteLine("Hello from C# In Console.");
            try
            {
                CKLBUILabel label = new CKLBUILabel(null, 1000, 300, 100, 0x00000000, "georgia", 16, "Hello World from C#!", CKLBUILabel.EALIGN.MID);
            }
            catch(Exception ex)
            {
                Console.WriteLine("##################################");
                Console.WriteLine("####### Exception Handling #######");
                Console.WriteLine("##################################");
                Console.WriteLine();
                Console.WriteLine("Exception Type : " + ex.GetType());
                Console.WriteLine();
                Console.WriteLine("Error Message : " + ex.Message);
                Console.WriteLine();
                Console.WriteLine("Stack Trace : " + ex.StackTrace);
            }
        }

    }
}
