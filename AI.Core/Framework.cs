using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using AI.Core.OperatorsImplimentation;

namespace AI.Core
{
    /// <summary>
    /// This class contains tope-level properties and methods
    /// </summary>
    public class Framework
    {
        private List<Type> _operatorsTypes;
        public Framework()
        {
            var targetAssembly = Assembly.GetExecutingAssembly();
            _operatorsTypes = targetAssembly.GetTypes().Where(t => t.IsSubclassOf(typeof(Operator))).ToList();
        }

        public List<Type> OperatorsTypes
        {
            get { return _operatorsTypes; }
        }
    }
}
