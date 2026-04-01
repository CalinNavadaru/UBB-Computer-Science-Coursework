import random

def generate_points_list(length, prob_not_solved, prob_fraudulent, starting_id):
    max_zeros = int(length * prob_not_solved / 100)
    max_minus_ones = int(length * prob_fraudulent / 100)
    
    rest_values = [random.randint(1, 10) for _ in range(length - max_zeros - max_minus_ones)]
    
    zeros = [0] * max_zeros
    minus_ones = [-1] * max_minus_ones
    
    final_list = rest_values + zeros + minus_ones
    random.shuffle(final_list)

    participants_list = [x for x in range(starting_id, starting_id + length + 1)]

    final_list = [(x, y) for x, y in zip(participants_list, final_list) if y != 0]
    
    return final_list

starting_id = 1
for country in range(1, 6):
    number_participants = random.randint(80, 100)
    for problem in range(1, 11):
        probability_fail = random.randint(0, 10)
        probability_cheat = random.randint(0, 2)
        result_list = generate_points_list(number_participants, probability_fail, probability_cheat, starting_id)

        with open(f"./data/C{country}_P{problem}.txt", "w") as f:
            for id, points in result_list:
                f.write(f"{id} {points}\n")
    starting_id = starting_id + number_participants + 1