#include "Olympicsa1.h"



Olympics::Olympics(): numberOfTeams(0), numberOfCountries(0), numberOfContestants(0),
countries(new Tree<Country>()),
teams(new Tree<Team>()),
contestants(new Tree<Contestant>()){
    // initializing the object
    // countries
    // teams
    // contestants
    // allCountries
    // allTeams
    // allContestants
}

// null parents

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

// not so sure about country->addTeam(), other than that the function looks good
StatusType Olympics::add_team(int teamId, int countryId, Sport sport){
    if(teamId <= 0 || countryId <= 0){
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<Country> country = countries->find(countryId);
    if(teams->contains(teamId) || !country){
        return StatusType::FAILURE;
    }

    try {
        shared_ptr<Team> team = make_shared<Team>(teamId, sport, country);
        teams->insert(team);
        country->addTeam(); // updates the number of teams in the country
    }catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }
    numberOfTeams++;
	return StatusType::SUCCESS;
}

// looks good I think
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

// looks good I think
StatusType Olympics::add_contestant(int contestantId ,int countryId, Sport sport,int strength){
    if(contestantId <= 0 || countryId <= 0 || strength < 0){
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Country> country = countries->find(countryId);

    if(!country || contestants->contains(contestantId)){
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

// looks good,
StatusType Olympics::remove_contestant(int contestantId){
    if(contestantId <= 0){
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<Contestant> contestant = contestants->find(contestantId);
//    check if the contestant is in a team
    if(!contestant || contestant->getNumOfActiveTeams() > 0){ // checks if the contestant is in a team if so return failure
        return StatusType::FAILURE;
    }

    try{
        contestants->remove(contestantId);
        contestant->getCountry().lock()->removeContestant();
    }catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }

    numberOfContestants--;
	return StatusType::SUCCESS;
}

// not final for sure
//TODO: decide whether team updates contestant itself or contestant does it himself. Should probably decide based on what makes implementing unite function easier.
StatusType Olympics::add_contestant_to_team(int teamId,int contestantId){
    if(teamId <= 0 || contestantId <= 0){
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<Team> team = teams->find(teamId);
    shared_ptr<Contestant> contestant = contestants->find(contestantId);

    // if he implemented it for a different use-case, roll-back to ->getNumOfActiveTeams()
    if(!team || !contestant
    || !contestant->isAvailable() // checks if the contestant is available for another team
    || contestant->getSport() != team->getSport() // checks sport's compatibility
    || contestant->getCountryID() != team->getCountryID() // checks nationality
    || contestant->isActiveInTeam(teamId)){ // checks whether the contestant is already part of the team
        return StatusType::FAILURE;
    }
    team->addContestant(contestant);
    //contestant->addTeam(team); //probably redundant because Omar added this to team->addContestant() but I commented it out

    return StatusType::SUCCESS;
}
//
// looks good. Omar did most of the work in the Team class
StatusType Olympics::remove_contestant_from_team(int teamId,int contestantId){
    if(teamId<=0 || contestantId <=0){
        return StatusType::INVALID_INPUT;
    }
    shared_ptr<Team> team = teams->find(teamId);
    shared_ptr<Contestant> contestant = contestants->find(contestantId);
    if(!team || !contestant || !contestant->isActiveInTeam(teamId)){
        return StatusType::FAILURE;
    }
    team->removeContestant(contestantId);
    //As of right now this is already done in team->removeContestant
    //contestant->removeTeam(teamId); // updates contestant's teams, necessary to keep.

	return StatusType::SUCCESS;
}


// changed contestant's fields to array of ints of teams' IDs
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


    // -----
    int numOfTeams = contestant->getNumOfActiveTeams();
    int tempTeams[numOfTeams];


    tempTeams[0] = contestant->getTeamID(0);
    tempTeams[1] = contestant->getTeamID(1);
    tempTeams[2] = contestant->getTeamID(2);

    for(int i = 0; i < MAX_TEAM_SIZE; i++){
        if(tempTeams[i] == -1) break;
        // removes the contestant from the team
        shared_ptr<Team> team = teams->find(tempTeams[i]);
        team->removeContestant(contestantId);
    }

    // updates the strength of the contestant
    contestant->updateStrength(change);




    for(int i = 0; i < numOfTeams; i++){
        shared_ptr<Team> team = teams->find(tempTeams[i]);
        team->addContestant(contestant);
    }


    return StatusType::SUCCESS;
}

// looks good
output_t<int> Olympics::get_strength(int contestantId){
    if(contestantId <= 0){
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    shared_ptr<Contestant> contestant = contestants->find(contestantId); // takes O(log(n)) time
    if(!contestant){
        return output_t<int>(StatusType::FAILURE);
    }
    return output_t<int>(contestant->getStrength()); // takes O(1) time
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
    if(teamId <= 0){
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    shared_ptr<Team> team = teams->find(teamId); // works in log(m) where m is the number of all teams in the olympics
    if(!team){
        return output_t<int>(StatusType::FAILURE);
    }

    return output_t<int>(team->getStrength()); //works in O(1)
}

// looks good, needs to be tested
StatusType Olympics::unite_teams(int teamId1,int teamId2){
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }
    // these 2 lines of code require O(logm) time
    shared_ptr<Team> team1 = teams->find(teamId1);
    shared_ptr<Team> team2 = teams->find(teamId2);

    if(!team1 || !team2 || (team1->getSport() != team2->getSport()) || (team1->getCountryID() != team2->getCountryID())){
        return StatusType::FAILURE;
    }

    try{
        // this updates team1 (takes O(N2) time)
        team1->uniteTeamsIntoThis(team2);
        // destroy team2
        teams->remove(teamId2); // this should effectively destruct team2 since it has no external references after we leave this scope.
        // update team2's country's number of teams
        team2->removeTeamFromItsCountry();
        // update the number of teams in the olympics
        numberOfTeams--;
    }catch (std::bad_alloc& e){
        return StatusType::ALLOCATION_ERROR;
    }

	return StatusType::SUCCESS;
}

StatusType Olympics::play_match(int teamId1,int teamId2){
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }
    // this code takes O(log(m)) time
    shared_ptr<Team> team1 = teams->find(teamId1);
    shared_ptr<Team> team2 = teams->find(teamId2);
    if(!team1 || !team2 || team1->getSport() != team2->getSport()){
        return StatusType::FAILURE;
    }

    // this code works in O(log(k)) time
    shared_ptr<Country> country1 = countries->find(team1->getCountryID());
    shared_ptr<Country> country2 = countries->find(team2->getCountryID());

    // this works in O(log(m)) time so we are ok =)
    int strength1 = get_team_strength(teamId1).ans() + country1->getMedals();
    int strength2 = get_team_strength(teamId2).ans() + country2->getMedals();

    if(strength1 > strength2){
        country1->addMedal();
    }
    else if(strength1 < strength2){
        country2->addMedal();
    }

    return StatusType::SUCCESS;
}

output_t<int> Olympics::austerity_measures(int teamId){
    if(teamId <= 0){
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    shared_ptr<Team> team = teams->find(teamId); // works in log(m) where m is the number of all teams in the olympics
    if(!team || (team->getNumberOfContestants() < 3)){
        return output_t<int>(StatusType::FAILURE);
    }
    return output_t<int>(team->getAusMeasure());
}
// TODO: this function was added for testing purposes. Must be removed later!
void Olympics::printTeam(int teamID) {
    auto team = teams->find(teamID);
    if(team == nullptr) return;
    team->print();
}

