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
using System.Collections.Generic;

namespace EnginePrototype
{
    // TODO is internal class accessible from C++ ?
    /// <summary>
    /// GameObject Factory class.
    /// Create a GameObject from its name.
    /// It will be usefull to create C# wrappers from C++ Game Engine.
    /// 
    /// It contains a <String, Type> Dictionary in order to be able to find a class type from its name.
    /// So it is possible to get an instance of a specific class which inherits GameObject.
    /// </summary>
    internal static class GameObjectFactory
    {
        // Not used at the moment
        /*private static Dictionary<String, Type> m_classes = new Dictionary<String,Type>();

        internal static GameObject getInstanceFromName(String className)
        {
            try
            {
                Type t = m_classes[className];
                return (GameObject)Activator.CreateInstance(t);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        internal static void registerType(String className, Type type) 
        {
            Console.WriteLine("[C#] GameObjectFactory.registerType(" + className + ", " + type.ToString() +") BEGIN");
            if(!m_classes.ContainsKey(className))
            {
                Console.WriteLine("[C#] GameObjectFactory.registerType add to m_classes");
                m_classes.Add(className, type);
                Console.WriteLine("[C#] GameObjectFactory.registerType END");
            }
            else
            {
                throw new CKLBException(className + " is already registered in GameObjectFactory");
            }
        }*/
    }
}
