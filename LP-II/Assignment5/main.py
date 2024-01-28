import json
from difflib import get_close_matches
import os

def load_kb(file_path: str) -> dict:
    """Loads knowledge base from JSON file."""
    with open(file_path, 'r') as kb_file:
        return json.load(kb_file)

def save_kb(file_path: str, knowledge_base: dict) -> None:
    """Saves knowledge base to JSON file."""
    with open(file_path, 'w') as kb_file:
        json.dump(knowledge_base, kb_file, indent=2)

class ChatBot:
    def __init__(self, knowledge_base_file: str):
        self.knowledge_base = load_kb(knowledge_base_file)

    def find_best_match(self, user_question: str) -> str or None:
        """Finds closest match to user's question in knowledge base."""
        potential_matches = get_close_matches(
            user_question, [q['question'] for q in self.knowledge_base['questions']], n=1, cutoff=0.5
        )
        return potential_matches[0] if potential_matches else None

    def get_answer(self, question: str) -> str or None:
        """Retrieves answer from knowledge base for given question."""
        for entry in self.knowledge_base['questions']:
            if entry['question'] == question:
                return entry['answer']
        return None

    def handle_user_input(self):
        """Handles user input and interacts with knowledge base."""
        while True:
            user_input = input("You: ")
            if user_input.lower() == "exit":
                break

            best_match = self.find_best_match(user_input)
            if best_match:
                answer = self.get_answer(best_match)
                print(f"Cometbot: {answer}")
            else:
                print("Bot: Sorry, I don't understand that. Can you please teach me?")
                new_answer = input("Type the answer or 'skip' to skip: ")
                if new_answer.lower() != "skip":
                    self.knowledge_base['questions'].append({'question': user_input, 'answer': new_answer})
                    save_kb(f"{os.path.dirname(os.path.realpath(__file__))}/knowledge_base.json", self.knowledge_base)
                    print("Bot: Thanks for teaching me!")

if __name__ == "__main__":
    chatbot = ChatBot(f"{os.path.dirname(os.path.realpath(__file__))}/knowledge_base.json")
    chatbot.handle_user_input()
