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
    if(medals < 0 || countryId <= 0){
        return StatusType::INVALID_INPUT;
    }

    if(countries->contains(countryId)){
        return StatusType::FAILURE;
    }

    try {
        shared_ptr<Country> country = make_shared<Country>(countryId, medals);
        countries->insert(country);
    }catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    numberOfCountries++;
	return StatusType::SUCCESS;
}
	
StatusType Olympics::remove_country(int countryId){
    if(countryId <= 0){
        return StatusType::INVALID_INPUT;
    }

    if(!countries->contains(countryId) || numberOfContestants > Zero || numberOfTeams > Zero){
        return StatusType::FAILURE;
    }

    try{
//        countries->remove(countryId);
    }catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    numberOfCountries--;
	return StatusType::SUCCESS;
}

StatusType Olympics::add_team(int teamId,int countryId,Sport sport){
    if(teamId <= 0 || countryId <= 0){
        return StatusType::INVALID_INPUT;
    }

    if(teams->contains(teamId) || !countries->contains(countryId)){
        return StatusType::FAILURE;
    }

    try {
        shared_ptr<Team> team = make_shared<Team>(teamId, countryId, sport);
        teams->insert(team);
    }catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    numberOfTeams++;
	return StatusType::SUCCESS;
}

// TODO: check if the team has contestants if so return failure
StatusType Olympics::remove_team(int teamId){
    if(teamId <= 0){
        return StatusType::INVALID_INPUT;
    }

    if(!teams->contains(teamId)){ // check if the team has contestants if so return failure
        return StatusType::FAILURE;
    }

    try{
//        teams->remove(teamId);
    }catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    numberOfTeams--;
    return StatusType::SUCCESS;
}
	
StatusType Olympics::add_contestant(int contestantId ,int countryId,Sport sport,int strength){
    if(contestantId <= 0 || countryId <= 0 || strength < 0){
        return StatusType::INVALID_INPUT;
    }

    if(contestants->contains(contestantId) || !countries->contains(countryId)){
        return StatusType::FAILURE;
    }

    try{
        shared_ptr<Contestant> contestant = make_shared<Contestant>(contestantId, countryId, sport, strength);
        contestants->insert(contestant);
    }catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    numberOfContestants++;
	return StatusType::SUCCESS;
}

// TODO: check if the contestant is in a team if so return failure
StatusType Olympics::remove_contestant(int contestantId){
    if(contestantId <= 0){
        return StatusType::INVALID_INPUT;
    }

    if(!contestants->contains(contestantId)){ // check if the contestant is in a team if so return failure
        return StatusType::FAILURE;
    }

    try{
//        contestants->remove(contestantId);
    }catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }

    numberOfContestants--;
	return StatusType::SUCCESS;
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



