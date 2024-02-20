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

// not so sure about country->addTeam()
StatusType Olympics::add_team(int teamId, int countryId, Sport sport){
    if(teamId <= 0 || countryId <= 0){
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Country> country = countries->find(countryId);
    if(teams->contains(teamId) || !country){
        return StatusType::FAILURE;
    }

    try {
        shared_ptr<Team> team = make_shared<Team>(teamId, country, sport);
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
        team->removeTeamFromItsCountry(); // updates the number of teams in the country
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
        shared_ptr<Contestant> contestant = make_shared<Contestant>(contestantId, country, sport, strength);
        contestants->insert(contestant);
        country->addContestant(); // updates the number of contestants in the country
    }catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    numberOfContestants++;
	return StatusType::SUCCESS;
}

// not so sure but looks good
StatusType Olympics::remove_contestant(int contestantId){
    if(contestantId <= 0){
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<Contestant> contestant = contestants->find(contestantId);
//    check if contestants is in a team
    if(!contestant || contestant->getNumOfActiveTeams() > 0){ // checks if the contestant is in a team if so return failure
        return StatusType::FAILURE;
    }

    try{
        contestant->removeFromTeams(); // updates the number of contestants in the contestant's teams
        contestant->removeFromCountry(); // updates the number of contestants in the contestant's country
        contestants->remove(contestantId);
    }catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }

    numberOfContestants--;
	return StatusType::SUCCESS;
}

// not so sure but looks good
StatusType Olympics::add_contestant_to_team(int teamId,int contestantId){
    if(teamId<=0 || contestantId <=0){
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<Team> team = teams->find(teamId);
    shared_ptr<Contestant> contestant = contestants->find(contestantId);
    if(!team || !contestant || contestant->getNumOfActiveTeams() >= MAX_TEAM_SIZE
    || contestant->getSport() != team->getSport()
    || contestant->getCountryID() != team->getCountryID()
    || contestant->isActiveInTeam(teamId)){
        return StatusType::FAILURE;
    }
    contestant->addTeam(team);
    team->addContestant();

    return StatusType::SUCCESS;
}

// not so sure but looks good.
StatusType Olympics::remove_contestant_from_team(int teamId,int contestantId){
    if(teamId<=0 || contestantId <=0){
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Team> team = teams->find(teamId);
    shared_ptr<Contestant> contestant = contestants->find(contestantId);
    if(!team || !contestant || !contestant->isActiveInTeam(teamId)){
        return StatusType::FAILURE;
    }
    team->removeContestant();
    contestant->removeTeam(teamId);

	return StatusType::SUCCESS;
}

// TODO: make sure to update the strength of the contestant's teams
StatusType Olympics::update_contestant_strength(int contestantId ,int change){
    if(contestantId <= 0){
        return StatusType::INVALID_INPUT;
    }
    // log(n) search time in the contestants tree
    // needed time is log(n) + log(m) where m is the number of teams
    // this probably is due to the fact that we need to update the strength of the teams
    shared_ptr<Contestant> contestant = contestants->find(contestantId);
    if(!contestant || contestant->getStrength() + change < 0){
        return StatusType::FAILURE;
    }
    contestant->updateStrength(change);
    return StatusType::SUCCESS;
}

// looks good
output_t<int> Olympics::get_strength(int contestantId){
    if(contestantId <= 0){
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    shared_ptr<Contestant> contestant = contestants->find(contestantId);
    if(!contestant){
        return output_t<int>(StatusType::FAILURE);
    }
    return output_t<int>(contestant->getStrength());
}

output_t<int> Olympics::get_medals(int countryId){
	if(countryId <= 0){
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    shared_ptr<Country> country = countries->find(countryId);
    if(!country){
        return output_t<int>(StatusType::FAILURE);
    }
    return output_t<int>(country->getMedals());
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



