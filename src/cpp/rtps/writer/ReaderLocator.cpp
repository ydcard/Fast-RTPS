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

/*
 * @file ReaderLocator.cpp
 *
 */

#include <fastrtps/rtps/writer/ReaderLocator.h>
#include <fastrtps/rtps/common/CacheChange.h>


namespace eprosima {
namespace fastrtps{
namespace rtps {

ReaderLocator::ReaderLocator() {
	this->expectsInlineQos = false;
	n_used = 1;

}

ReaderLocator::ReaderLocator(Locator_t& a_locator, bool expectsQos ){
	locator = a_locator;
	expectsInlineQos = expectsQos;
	n_used = 1;
}

ReaderLocator::~ReaderLocator()
{
	//pDebugInfo("ReaderLocator destructor"<<endl;);
}

//void ReaderLocator::requested_changes_set(std::vector<SequenceNumber_t>& seqs,GUID_t& myGUID,HistoryCache* history) {
//	std::vector<SequenceNumber_t>::iterator it;
//	requested_changes.clear();
//	for(it = seqs.begin();it!=seqs.end();++it)
//	{
//		CacheChange_t** cpoin = NULL;
//
//		if(history->get_change(*it,myGUID,cpoin))
//			requested_changes.push_back(*cpoin);
//	}
//}

bool ReaderLocator::remove_requested_change(CacheChange_t* cpoin){
	std::vector<const CacheChange_t*>::iterator it;
	for(it=requested_changes.begin();it!=requested_changes.end();++it)
	{
		if(cpoin == *it)
		{
			requested_changes.erase(it);
			return true;
		}
	}
	return false;

}

bool ReaderLocator::remove_unsent_change(CacheChange_t* cpoin)
{
	for(auto it = unsent_changes.begin(); it != unsent_changes.end(); ++it)
	{
		if(cpoin->sequenceNumber == it->getChange()->sequenceNumber)
		{
			unsent_changes.erase(it);
			return true;
		}
	}
	return false;
}
}
} /* namespace rtps */
} /* namespace eprosima */


