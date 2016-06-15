// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file Publisher.h 	
 */



#ifndef PUBLISHERIMPL_H_
#define PUBLISHERIMPL_H_
#ifndef DOXYGEN_SHOULD_SKIP_THIS_PUBLIC

#include <fastrtps/rtps/common/Locator.h>
#include <fastrtps/rtps/common/Guid.h>

#include <fastrtps/attributes/PublisherAttributes.h>

#include <fastrtps/publisher/PublisherHistory.h>

#include <fastrtps/rtps/writer/WriterListener.h>

namespace eprosima {
namespace fastrtps{
namespace rtps
{
class RTPSWriter;
class RTPSParticipant;
}

using namespace rtps;



class TopicDataType;
class PublisherListener;
class ParticipantImpl;
class Publisher;


/**
 * Class PublisherImpl, contains the actual implementation of the behaviour of the Publisher.
 * @ingroup FASTRTPS_MODULE
 */
class PublisherImpl {
	friend class ParticipantImpl;
public:

	/**
	 * Create a publisher, assigning its pointer to the associated writer.
	 * Don't use directly, create Publisher using DomainRTPSParticipant static function.
	 */
	PublisherImpl(ParticipantImpl* p,TopicDataType* ptype,
			PublisherAttributes& att,PublisherListener* p_listen = nullptr);

	virtual ~PublisherImpl();

	/**
	 * 
	 * @param kind
	 * @param  Data
	 * @return
	 */
	bool create_new_change(ChangeKind_t kind, void* Data);

	/**
	 * 
	 * @param kind
	 * @param  Data
     * @param wparams
	 * @return
	 */
	bool create_new_change_with_params(ChangeKind_t kind, void* Data, WriteParams &wparams);

	/**
	 * Removes the cache change with the minimum sequence number
	 * @return True if correct.
	 */
	bool removeMinSeqChange();
	/**
	 * Removes all changes from the History.
	 * @param[out] removed Number of removed elements
	 * @return True if correct.
	 */
	bool removeAllChange(size_t* removed);

	/**
	 * Get the number of elements in the History.
	 * @return Number of elements in the History.
	 */
	size_t getHistoryElementsNumber();

	/**
	 * 
	 * @return
	 */
	const GUID_t& getGuid();

	/**
	 * Update the Attributes of the publisher;
	 * @param att Reference to a PublisherAttributes object to update the parameters;
	 * @return True if correctly updated, false if ANY of the updated parameters cannot be updated
	 */
	bool updateAttributes(PublisherAttributes& att);

	/**
	 * Get the Attributes of the Subscriber.
	 * @return Attributes of the Subscriber.
	 */
	inline const PublisherAttributes& getAttributes(){ return m_att; };

	/**
	* Get topic data type
	* @return Topic data type
	*/
	TopicDataType* getType() {return mp_type;};

    bool clean_history(unsigned int max = 0);

    bool wait_for_all_acked(const Time_t& max_wait);

private:
	ParticipantImpl* mp_participant;
	//! Pointer to the associated Data Writer.
	RTPSWriter* mp_writer;
	//! Pointer to the TopicDataType object.
	TopicDataType* mp_type;
	//!Attributes of the Publisher
	PublisherAttributes m_att;
	//!Publisher History
	PublisherHistory m_history;
	//!PublisherListener
	PublisherListener* mp_listener;
	//!Listener to capture the events of the Writer
	class PublisherWriterListener: public WriterListener
	{
	public:
		PublisherWriterListener(PublisherImpl* p):mp_publisherImpl(p){};
		virtual ~PublisherWriterListener(){};
		void onWriterMatched(RTPSWriter* writer,MatchingInfo& info);
		PublisherImpl* mp_publisherImpl;
	}m_writerListener;

	Publisher* mp_userPublisher;

	RTPSParticipant* mp_rtpsParticipant;

};


} /* namespace  */
} /* namespace eprosima */
#endif
#endif /* PUBLISHER_H_ */
