#pragma once

#include "Contact.h"

namespace AI
{
	namespace Core
	{
		namespace ChannelsImplimentation
		{
			/// <summary>
			/// Channel object
			/// </summary>
			class Channel final
			{
				/// <summary>
				/// Current number of quantum's in channel. There is a question about uint type. We should see on memory usage and change it if that will be useful.
				/// </summary>
			public:
				unsigned long long Value;

			private:
				const Contact _fromContact;
				const Contact _toContact;

			public:
				Channel(Contact fromContact, Contact toContact);

				/// <summary>
				/// Returns contact's number for exit operator
				/// </summary>
				const Contact &getFromContact() const;

				/// <summary>
				/// Returns contact's number for enter operator
				/// </summary>
				const Contact &getToContact() const;

			private:
				void InitializeInstanceFields();
			};
		}
	}
}
