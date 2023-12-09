#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>

std::vector<std::string> hands;
std::vector<std::string> high_cards;
std::vector<std::string> pairs;
std::vector<std::string> two_pairs;
std::vector<std::string> three_of_a_kinds;
std::vector<std::string> full_houses;
std::vector<std::string> four_of_a_kinds;
std::vector<std::string> five_of_a_kinds;

std::unordered_map<char, int> card_value = {

    {'J', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7},
    {'8', 8}, {'9', 9}, {'T', 10}, {'Q', 12}, {'K', 13}, {'A', 14}

};

std::unordered_map<std::string, int> hands_to_bids;

// ritorna true se vince hand1, false altrimenti
// assume no parità
bool sort_rule(std::string hand1, std::string hand2) {

    for (int i = 0; i < hand1.size(); i++) {

        if (card_value.find(hand1[i])->second > card_value.find(hand2[i])->second) {

            return true;

        } else if (card_value.find(hand1[i])->second < card_value.find(hand2[i])->second) {

            return false;

        } else {
            continue;
        }

    }

    return false; // superfluo

}

int calculate_type(std::string hand) {

    int type = 0;

    hand.erase(std::remove(hand.begin(), hand.end(), 'J'), hand.end());
    int joker_counter = 5 - hand.size();

    std::unordered_map<char, int> cardCount;

    for (char card : hand) {
        cardCount[card]++;
    }

    if (joker_counter != 0) {
    
        int best_card_occ = 0;
        char best_card;
        
        for (const auto& pair : cardCount) {

            if (pair.second > best_card_occ) {
                best_card_occ = pair.second;
                best_card = pair.first;
            } else if (pair.second == best_card_occ) {
                
                int this_card_value = card_value.find(pair.first)->second;
                int best_card_value = card_value.find(best_card)->second;

                if (this_card_value > best_card_value) {

                    best_card_occ = pair.second;
                    best_card = pair.first;

                }
            }
            
        }

        for (int i = 0; i < joker_counter; i++) {
            cardCount[best_card]++;
        }

    }

    int distinctCards = cardCount.size();

    switch (distinctCards) {
        case 1:
            type = 7; // five of a kind
            break;
        case 2:
            if (std::any_of(cardCount.begin(), cardCount.end(),
                            [](const auto& entry) { return entry.second == 4; })) {
                type = 6; // four of a kind
            } else {
                type = 5; // full house
            }
            break;
        case 3:
            if (std::any_of(cardCount.begin(), cardCount.end(),
                            [](const auto& entry) { return entry.second == 3; })) {
                type = 4; // three of a kind
            } else {
                type = 3; // two pair
            }
            break;
        case 4:
            type = 2; // pair
            break;
        case 5:
            type = 1; // high card
            break;
        default:
            return -1; // invalid hand
    }

    return type;

}

void bubble_sort_by_card(std::vector<std::string> &cards) {

    if (cards.size() == 0) {
        return;
    }

    bool swapped;

    for (int i = 0; i < cards.size() - 1; i++) {
        swapped = false;

        for (int j = 0; j < cards.size() - i - 1; j++) {

            if (sort_rule(cards[j], cards[j+1])) {
                std::swap(cards[j], cards[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }

    }

}

int main() {

    std::ifstream file("inputs/day7_input.txt");
    // std::ifstream file("inputs/day7_input_example.txt");

    std::string line;

    // leggi file e popola hands & bids
    if (file.is_open()) {

        while (std::getline(file, line)) {

            std::istringstream iss(line);
            std::string hand, bid;
            iss >> hand;
            std::getline(iss, bid);
            hands.push_back(hand);   

            hands_to_bids.insert(std::make_pair(hand, std::stoi(bid)));

        }

    }

    file.close();

    // assegna tipo hand
    for (int i = 0; i < hands.size(); i++) {

        switch(calculate_type(hands[i])) {

            case 1:
                high_cards.push_back(hands[i]);
                break;
            case 2:
                pairs.push_back(hands[i]);
                break;
            case 3:
                two_pairs.push_back(hands[i]);
                break;
            case 4:
                three_of_a_kinds.push_back(hands[i]);
                break;
            case 5:
                full_houses.push_back(hands[i]);
                break;
            case 6:
                four_of_a_kinds.push_back(hands[i]);
                break;
            case 7:
                five_of_a_kinds.push_back(hands[i]);
                break;
            default:
                break;

        }

    }

    bubble_sort_by_card(high_cards);
    bubble_sort_by_card(pairs);
    bubble_sort_by_card(two_pairs);
    bubble_sort_by_card(three_of_a_kinds);
    bubble_sort_by_card(full_houses);
    bubble_sort_by_card(four_of_a_kinds);
    bubble_sort_by_card(five_of_a_kinds);

    std::vector<std::string> sorted_hands;

    sorted_hands.insert(sorted_hands.end(), high_cards.begin(), high_cards.end());
    sorted_hands.insert(sorted_hands.end(), pairs.begin(), pairs.end());
    sorted_hands.insert(sorted_hands.end(), two_pairs.begin(), two_pairs.end());
    sorted_hands.insert(sorted_hands.end(), three_of_a_kinds.begin(), three_of_a_kinds.end());
    sorted_hands.insert(sorted_hands.end(), full_houses.begin(), full_houses.end());
    sorted_hands.insert(sorted_hands.end(), four_of_a_kinds.begin(), four_of_a_kinds.end());
    sorted_hands.insert(sorted_hands.end(), five_of_a_kinds.begin(), five_of_a_kinds.end());

    int sum = 0;

    for (int i = 0; i < sorted_hands.size(); i++) {

        sum += (i+1) * hands_to_bids.find(sorted_hands[i])->second;

    }

    std::cout << sum << std::endl;

    return 0;

}