#include "Olympicsa1.h"



Olympics::Olympics(){
    // default constructor
}

Olympics::~Olympics(){
    // destructing the object
    // countries
    // teams
    // contestants
}
	
StatusType Olympics::add_country(int countryId, int medals){
    if(countries->contains(countryId)){
        return StatusType::FAILURE;
    }

    try {
        shared_ptr<Country> country = make_shared<Country>(countryId, medals);
        countries->insert(country);
    }catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }

	return StatusType::SUCCESS;
}
	
StatusType Olympics::remove_country(int countryId){
	return StatusType::FAILURE;
}

StatusType Olympics::add_team(int teamId,int countryId,Sport sport){
	return StatusType::FAILURE;
}

StatusType Olympics::remove_team(int teamId){
	return StatusType::FAILURE;
}
	
StatusType Olympics::add_contestant(int contestantId ,int countryId,Sport sport,int strength){
	return StatusType::FAILURE;
}
	
StatusType Olympics::remove_contestant(int contestantId){
	return StatusType::FAILURE;
}
	
StatusType Olympics::add_contestant_to_team(int teamId,int contestantId){
	return StatusType::FAILURE;
}

StatusType Olympics::remove_contestant_from_team(int teamId,int contestantId){
	return StatusType::FAILURE;
}

StatusType Olympics::update_contestant_strength(int contestantId ,int change){
	return StatusType::FAILURE;
}

output_t<int> Olympics::get_strength(int contestantId){
	return 0;
}

output_t<int> Olympics::get_medals(int countryId){
	return 0;
}

output_t<int> Olympics::get_team_strength(int teamId){
	return 0;
}

StatusType Olympics::unite_teams(int teamId1,int teamId2){
	return StatusType::FAILURE;
}

StatusType Olympics::play_match(int teamId1,int teamId2){
	return StatusType::FAILURE;
}

output_t<int> Olympics::austerity_measures(int teamId){
	return 0;
}



