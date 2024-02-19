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

// looks good
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

// looks good
StatusType Olympics::remove_country(int countryId){
    if(countryId <= 0){
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<Country> country = countries->find(countryId);
    if(!country || country->getNumberOfContestants() > 0 || country->getNumberOfTeams() > 0){
        return StatusType::FAILURE;
    }

    try{
        countries->remove(countryId);
    }catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    numberOfCountries--;
	return StatusType::SUCCESS;
}

// not so sure, team's constructor should take a pointer to country and not int countryId
StatusType Olympics::add_team(int teamId, int countryId, Sport sport){
    if(teamId <= 0 || countryId <= 0){
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Country> country = countries->find(countryId);
    if(teams->contains(teamId) || !country){
        return StatusType::FAILURE;
    }

    try {
        shared_ptr<Team> team = make_shared<Team>(teamId, countryId, sport);
        teams->insert(team);
        country->addTeam(); // updates the number of teams in the country
    }catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    numberOfTeams++;
	return StatusType::SUCCESS;
}

// no so sure
StatusType Olympics::remove_team(int teamId){
    if(teamId <= 0){
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<Team> team = teams->find(teamId);
    if(!team || team->getNumberOfContestants() > 0){
        return StatusType::FAILURE;
    }

    try{
//        team->myCountry->removeTeam(); // updates the number of teams in the country
        teams->remove(teamId);
    }catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    numberOfTeams--;
    return StatusType::SUCCESS;
}

// not so sure about country->addContestant()
StatusType Olympics::add_contestant(int contestantId ,int countryId, Sport sport,int strength){
    if(contestantId <= 0 || countryId <= 0 || strength < 0){
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Country> country = countries->find(countryId);

    if(contestants->contains(contestantId) || !country){
        return StatusType::FAILURE;
    }

    try{
        shared_ptr<Contestant> contestant = make_shared<Contestant>(contestantId, countryId, sport, strength);
        contestants->insert(contestant);
        country->addContestant(); // TODO implement
    }catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    numberOfContestants++;
	return StatusType::SUCCESS;
}

// TODO: implement contestant->getNumOfActiveTeams()
StatusType Olympics::remove_contestant(int contestantId){
    if(contestantId <= 0){
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<Contestant> contestant = contestants->find(contestantId);
//    check if contestants is in a team
//  if(!contestant || contestant->getNumOfActiveTeams() > Zero){ // checks if the contestant is in a team if so return failure
//        return StatusType::FAILURE;
//    }
    try{
        contestants->remove(contestantId);
    }catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }

    numberOfContestants--;
	return StatusType::SUCCESS;
}

// TODO: implement contestant->getNumberOfActiveTeams(), contestant->isActiveInTeam(int teamId)
StatusType Olympics::add_contestant_to_team(int teamId,int contestantId){
    if(teamId<=0 || contestantId <=0){
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<Team> team = teams->find(teamId);
    shared_ptr<Contestant> contestant = contestants->find(contestantId);
//    if(!team || !contestant || contestant->getNumOfActiveTeams() > MAX_TEAM_SIZE
//    || contestant->getSport() != team->getSport()
//    || contestant->isActiveInTeam(teamId)){
//        return StatusType::FAILURE;
//    }

//    team->addContestant(contestant);
//    team->numberOfContestants++;

    return StatusType::SUCCESS;
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



