namespace AI.Core.ChannelsImplimentation
{
    /// <summary>
    /// Channel object
    /// </summary>
    public sealed class Channel
    {
        /// <summary>
        /// Current number of quantum's in channel. There is a question about uint type. We should see on memory usage and change it if that will be useful.
        /// </summary>
        public ulong Value;

        private readonly Contact _fromContact;
        private readonly Contact _toContact;

        public Channel(Contact fromContact, Contact toContact)
        {
            _fromContact = fromContact;
            _toContact = toContact;
        }

        /// <summary>
        /// Returns contact's number for exit operator
        /// </summary>
        public Contact FromContact
        {
            get { return _fromContact; }
        }

        /// <summary>
        /// Returns contact's number for enter operator
        /// </summary>
        public Contact ToContact
        {
            get { return _toContact; }
        }
    }
}
