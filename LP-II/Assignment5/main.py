import json
from difflib import get_close_matches
import os

current_directory = os.path.dirname(os.path.realpath(__file__))

def load_knowledge_base(file_path:str)-> dict:
    with open(file_path,'r') as file:
        data = json.load(file)
    return data

def save_knowledge_base(file_path:str, data:dict):
    with open(file_path,'w') as file:
        json.dump(data, file, indent=2)

def find_best_match(user_question:str, questions:list)-> str or None:
    matches = get_close_matches(user_question, questions, n=1, cutoff=0.6)
    return matches[0] if matches else None

def get_answer_for_question(question:str, knowledge_base:dict)-> str or None:
    for q in knowledge_base["questions"]:
        if q["question"] == question:
            return q["answer"]

def chatBot():
    knowledge_base = load_knowledge_base(f"{current_directory}/knowledge_base.json")
    while True:
        user_input = input("You: ")
        if user_input.lower() == "exit":
            break

        best_match = find_best_match(user_input, [q["question"] for q in knowledge_base["questions"]])

        if best_match:
            answer = get_answer_for_question(best_match, knowledge_base) 
            print(f"Cometbot: {answer}")
        else:
            print("Bot: Sorry, I don't understand that. Can you please teach me?")
            new_answer = input("Type the answer or 'skip' to skip: ")

            if new_answer.lower() == "skip":
                continue
            else:
                knowledge_base["questions"].append({"question":user_input, "answer":new_answer})
                save_knowledge_base(f"{current_directory}/knowledge_base.json", knowledge_base)
                print("Bot: Thanks for teaching me")

if __name__ == "__main__":
    chatBot()
