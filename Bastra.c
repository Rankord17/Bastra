#include <stdio.h>
#include "Bastra.h"


int main(void) {
    Card initial_deck[max_cards], shuffled_deck[max_cards], player_one[4], player_two[4], player_three[4], player_four[4], board_cards[20];
    int turn = 0, player_card_index, player1_points = 0, player2_points = 0, player3_points = 0, player4_points = 0, winner = 0;
    printf(" ...Welcome to the Bastra game... \n");
    sleep(1);
    printf(" ...Let's begin the game... \n");
    sleep(1);
    initialize(initial_deck);
    while (true) {
        int round = 1, card_number = 0;
        printf(" ...Shuffling the deck...\n");
        sleep(2);

        shuffle(shuffled_deck);
        for (int board_reset = 0; board_reset <= 19; board_reset++){
            board_cards[board_reset].suit = 0;
            board_cards[board_reset].rank = 0;
        }
        card_number = board_distribution(card_number, board_cards, shuffled_deck);
        printf("Dealing cards on the board...\n");
        while (true) {
            printf("\n");
            sleep(1);
            printf("Distributing cards among players...\n");
            sleep(2);
            int use = 1;
            card_number = player_distribution(card_number, shuffled_deck, player_one, player_two, player_three, player_four);
            while (true){
                int action = 0;
                turn = turn % 4 + 1;

                board_display(board_cards); // For showing the state of the game
                sleep(1);
                switch(turn) {
                    case 1: player_display(turn, player_one);
                    break;
                    case 2: player_display(turn, player_two);
                    break;
                    case 3: player_display(turn, player_three);
                    break;
                    case 4: player_display(turn, player_four);
                    break;
                }
                while (true) {
                    int adviced_c;
                    switch (turn) {
                        case 1:
                        {
                            adviced_c = adviced_card(player_one, board_cards);
                            adviced_display(player_one[adviced_c]);
                        }
                        break;
                        case 2:
                        {
                            adviced_c = adviced_card(player_two, board_cards);
                            adviced_display(player_two[adviced_c]);
                        }
                        break;
                        case 3:
                        {
                            adviced_c = adviced_card(player_three, board_cards);
                            adviced_display(player_three[adviced_c]);
                        }
                        break;
                        case 4:
                        {
                            adviced_c = adviced_card(player_four, board_cards);
                            adviced_display(player_four[adviced_c]);
                        }
                        break;
                    }
                    sleep(1);
                    printf("\nWhich card do you want to play? Enter the index:");
                    scanf("%i", &player_card_index);
                    player_card_index--;

                    if (player_card_index >= 4)
                        printf("The card in the entered index doesn't exist. Please, try to enter the index again.\n");
                    else if (turn == 1 && player_one[player_card_index].suit != 0 && player_one[player_card_index].rank != 0)
                        break;
                    else if (turn == 2 && player_two[player_card_index].suit != 0 && player_two[player_card_index].rank != 0)
                        break;
                    else if (turn == 3 && player_three[player_card_index].suit != 0 && player_three[player_card_index].rank != 0)
                        break;
                    else if (turn == 4 && player_four[player_card_index].suit != 0 && player_four[player_card_index].rank != 0)
                        break;
                    else
                        printf("The card in the entered index doesn't exist. Please, try to enter the index again.\n");
                }

                switch(turn) {
                    case 1: action = which_action(player_one[player_card_index], board_cards);
                    break;
                    case 2: action = which_action(player_two[player_card_index], board_cards);
                    break;
                    case 3: action = which_action(player_three[player_card_index], board_cards);
                    break;
                    case 4: action = which_action(player_four[player_card_index], board_cards);
                    break;
                    }
                    if (action == 0){ // If player puts the card on the board
                        for (int index = 0; index <= 19; index++) {
                            if (board_cards[index].rank == 0) {
                                switch (turn) {
                                    case 1: { board_cards[index].suit = player_one[player_card_index].suit;
                                        board_cards[index].rank = player_one[player_card_index].rank; }
                                    break;
                                    case 2: { board_cards[index].suit =player_two[player_card_index].suit;
                                        board_cards[index].rank = player_two[player_card_index].rank; }
                                    break;
                                    case 3: { board_cards[index].suit =player_three[player_card_index].suit;
                                        board_cards[index].rank = player_three[player_card_index].rank; }
                                    break;
                                    case 4: { board_cards[index].suit = player_four[player_card_index].suit;
                                        board_cards[index].rank = player_four[player_card_index].rank; }
                                    break;
                                    }
                                    break;
                                }
                            }
                        }
                    else if (action == 1) {// For checking if the ranks of the player card and the board card are same
                        for (int index = 0; index <= 19; index++) {
                            switch(turn) {
                                case 1:
                                {
                                    if (board_cards[index].rank == player_one[player_card_index].rank) {
                                        removing_board_card(index, board_cards);
                                        player1_points++;
                                    }
                                }
                                break;
                                case 2:
                                {
                                    if (board_cards[index].rank == player_two[player_card_index].rank) {
                                        removing_board_card(index, board_cards);
                                        player2_points++;
                                    }
                                }
                                break;
                                case 3:
                                {
                                    if (board_cards[index].rank == player_three[player_card_index].rank) {
                                        removing_board_card(index, board_cards);
                                        player3_points++;
                                    }
                                }
                                break;
                                case 4:
                                {
                                    if (board_cards[index].rank == player_four[player_card_index].rank) {
                                        removing_board_card(index, board_cards);
                                        player4_points++;
                                    }
                                }
                                break;
                            }
                        }
                    }

                    else if (action == 2) {// Checks if the sum of 2 ranks of the board cards are equal to the rank of the player card
                        int done = 0;
                        for (int difference = 1; difference <= 19; difference++) {
                            if (turn == 1) {
                                for (int index = 0; index <= 19; index++) {
                                    if (index + difference <= 19) {
                                        if (player_one[player_card_index].rank == board_cards[index].rank + board_cards[index + difference].rank) {
                                            removing_board_card(index, board_cards);
                                            removing_board_card(index + difference, board_cards);

                                        done += 1;
                                    }
                                }
                            }
                        }
                        else if (turn == 2) {
                            for (int index = 0; index <= 19; index++) {
                                if (index + difference <= 19) {
                                    if (player_two[player_card_index].rank == board_cards[index].rank + board_cards[index + difference].rank) {
                                        removing_board_card(index, board_cards);
                                        removing_board_card(index + difference,board_cards);

                                        done += 1;
                                    }
                                }
                            }
                        }
                        else if (turn == 3) {
                            for (int index = 0; index <= 19; index++) {
                                if (index + difference <= 19) {
                                    if (player_three[player_card_index].rank == board_cards[index].rank + board_cards[index + difference].rank) {
                                        removing_board_card(index, board_cards);
                                        removing_board_card(index + difference, board_cards);

                                        done += 1;
                                    }
                                }
                            }
                        }
                        else if (turn == 4) {
                            for (int index = 0; index <= 19; index++) {
                                if (index + difference <= 19) {
                                    if (player_four[player_card_index].rank == board_cards[index].rank + board_cards[index + difference].rank) {
                                        removing_board_card(index, board_cards);
                                        removing_board_card(index + difference, board_cards);

                                        done += 1;
                                    }
                                }
                            }
                        }
                    }

                    switch(turn) // For giving points to the player depending on how many cards he has taken
                    {
                        case 1: player1_points += done;
                        break;
                        case 2: player2_points += done;
                        break;
                        case 3: player3_points += done;
                        break;
                        case 4: player4_points += done;
                        break;
                    }
                }
                else if (action == 3) {// If the card with the suit "Jack" was played
                    for (int b_index = 0; b_index <= 19; b_index++){ // Removes all board cards
                        removing_board_card(b_index, board_cards);
                    }

                    switch(turn) // Gives the player 1 point for using "Jack"
                    {
                        case 1: player1_points++;
                        break;
                        case 2: player2_points++;
                        break;
                        case 3: player3_points++;
                        break;
                        case 4: player4_points++;
                        break;
                    }
                }

                if (action != 0) {// Gives additional points if the played card was "2 Clubs" or "10 Diamonds"
                    switch (turn)
                    {
                        case 1: player1_points += bonus_points(player_one[player_card_index]);
                        break;
                        case 2: player2_points += bonus_points(player_two[player_card_index]);
                        break;
                        case 3: player3_points += bonus_points(player_three[player_card_index]);
                        break;
                        case 4: player4_points += bonus_points(player_four[player_card_index]);
                        break;
                    }
                }
                if (action != 3) {
                    switch(turn) // Checks if there's a Bastra on the board
                    {
                        case 1: player1_points += bastra_check(player1_points, turn, board_cards);
                        break;
                        case 2: player2_points += bastra_check(player2_points, turn, board_cards);
                        break;
                        case 3: player3_points += bastra_check(player3_points, turn, board_cards);
                        break;
                        case 4: player4_points += bastra_check(player4_points, turn, board_cards);
                        break;
                    }
                }
                // Removing card from player
                switch (turn)
                {
                    case 1: removing_player_card(player_card_index, player_one);
                    break;
                    case 2: removing_player_card(player_card_index, player_two);
                    break;
                    case 3: removing_player_card(player_card_index, player_three);
                    break;
                    case 4: removing_player_card(player_card_index, player_four);
                    break;
                }
                if (use == 16) // Checks if round has been ended or not
                    break;
                else
                    use++;
            }

            if (round == 3) // Checks if all 52 cards has been used or not
                break;
            else
                round++;
        }
        printf("Points: Player 1: %i | Player 2: %i | Player 3: %i | Player 4: %i\n", player1_points, player2_points, player3_points, player4_points);
        sleep(2);
        // For checking if there's a winner
        if (player1_points >= 100) {
            winner = 1;
            break;
        }
        else if (player2_points >= 100) {
            winner = 2;
            break;
        }
        else if (player3_points >= 100) {
            winner = 3;
            break;
        }
        else if (player4_points >= 100) {
            winner = 4;
            break;
        }
        else {// If there's no winner, then the cards will be shuffled again
            printf("All cards has been used, clearing the board and reshuffling the cards...\n");
            sleep(1);
        }
    }

    switch(winner)
    {
        case 1: printf("Player 1 has won. Congratulations!\n");
        break;
        case 2: printf("Player 2 has won. Congratulations!\n");
        break;
        case 3: printf("Player 3 has won. Congratulations!\n");
        break;
        case 4: printf("Player 4 has won. Congratulations!\n");
        break;
    }
}