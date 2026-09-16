"""Functions for tracking poker hands and assorted card tasks.

Python list documentation: https://docs.python.org/3/tutorial/datastructures.html
"""


def get_rounds(number):
    """Create a list containing the current and next two round numbers.

    Parameters:
        number (int): The current round number.

    Returns:
        list: The current round number and the two that follow.
    """
    return [number, number + 1, number + 2]


def concatenate_rounds(rounds_1, rounds_2):
    """Concatenate two lists of round numbers.

    Parameters:
        rounds_1 (list): The first rounds played.
        rounds_2 (list): The second group of rounds played.

    Returns:
        list:  All rounds played.
    """

    return rounds_1 + rounds_2



def list_contains_round(rounds, number):
    """Check if the list of rounds contains the specified number.

    Parameters:
        rounds (list): The rounds played.
        number (int): The round number.

    Returns:
        bool: Was the round played?
    """
    for round in rounds:
        if number == round:
            return True
    return False


def card_average(hand):
    """Calculate and returns the average card value from the list.

    Parameters:
        hand (list): The cards in the hand.

    Returns:
        float: The average value of the cards in the hand.
    """
    return sum(hand) / len(hand)

def approx_average_is_average(hand):
    """Return if the (average of first and last card values) OR ('middle' card) == calculated average.

    Parameters:
        hand (list): The cards in the hand.

    Returns:
        bool: Does one of the approximate averages equal the `true average`?
    """
    # 1. Calculate the true average
    true_avg = sum(hand) / len(hand)
    
    # 2. Strategy 1: Average of the first and last card
    first_last_avg = (hand[0] + hand[-1]) / 2
    
    # 3. Strategy 2: The middle card (median)
    middle_card = hand[len(hand) // 2]
    
    # Return True if either strategy matches the true average
    return true_avg == first_last_avg or true_avg == middle_card



def average_even_is_average_odd(hand):
    """Return if the (average of even indexed card values) == (average of odd indexed card values).

    Parameters:
        hand (list): The cards in the hand.

    Returns:
        bool: Are the even and odd averages equal?
    """
    # 1. Extract cards at even positions (0, 2, 4...) and odd positions (1, 3, 5...)
    even_cards = hand[0::2]
    odd_cards = hand[1::2]
    
    # 2. Calculate the averages
    even_avg = sum(even_cards) / len(even_cards)
    odd_avg = sum(odd_cards) / len(odd_cards)
    
    # 3. Check if they are equal
    return even_avg == odd_avg



def maybe_double_last(hand):
    """Multiply a Jack card value in the last index position by 2.

    Parameters:
        hand (list): The cards in the hand.

    Returns:
        list: The hand with Jacks (if present) value doubled.
    """
    if hand[-1] == 11:
        hand[-1] = 22  # 11 * 2
    return hand
