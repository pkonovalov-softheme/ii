using System.Collections.Generic;

namespace AI.Core.OperatorsImplimentation
{
    /// <summary>
    /// Dictionary collection of Entity Operators
    /// </summary>
    public class Operators : Dictionary<ulong, Operator>
    {
        private ulong _currentId;

        /// <summary>
        /// Returns new unique Operator Id that is used for Operator creation and for Operator adding to Operators dictionary
        /// </summary>
        public ulong GetNewUniqueId()
        {
            do
            {
                _currentId++;
            } while (ContainsKey(_currentId));

            return _currentId;
        }
    }
}
