import socket
import sys
import re
import time

class PuzzleClient:
    def __init__(self,host,port):
        self.host = host
        self.port = port
        self.socket = None
        self.connected = False
        self.remaining_data = ""  
    
    def connect(self):
        try:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.connect((self.host, self.port))
            self.connected = True
            print(f"Connected to server at {self.host}:{self.port}")
            return True
        except ConnectionRefusedError:
            print("Error: Connection refused. Is the server running?")
        except Exception as e:
            print(f"Error connecting to server: {e}")
        
        return False
    
    def receive_complete_message(self):
        buffer = self.remaining_data  
        
        complete_puzzle_pattern = r"Puzzle \d+.*?Grid:.*?Words to find:.*?Enter Teleword:"
        complete_result_pattern = r"(Correct!|Incorrect!)"
        complete_congrats_pattern = r"Congratulations!.*?flag\{.*?\}"
        
        while True:
            try:
                chunk = self.socket.recv(4096).decode('utf-8')
                if not chunk:
                    print("Disconnected from server.")
                    self.connected = False
                    return buffer if buffer else None
                
                buffer += chunk
                
                puzzle_match = re.search(complete_puzzle_pattern, buffer, re.DOTALL)
                if puzzle_match:
                    match_end = puzzle_match.end()
                    message = buffer[:match_end]
                    self.remaining_data = buffer[match_end:]
                    return message
                
                result_match = re.search(complete_result_pattern, buffer)
                if result_match and not re.search(r"Puzzle \d+", buffer):
                    match_end = result_match.end()
                    message = buffer[:match_end]
                    self.remaining_data = buffer[match_end:]
                    return message
                
                if result_match and "Puzzle" in buffer and "Grid:" in buffer:
                    result_end = buffer.find("=", result_match.end())
                    if result_end > 0:
                        message = buffer[:result_end]
                        self.remaining_data = buffer[result_end:]
                        return message
                
                congrats_match = re.search(complete_congrats_pattern, buffer, re.DOTALL)
                if congrats_match:
                    match_end = congrats_match.end()
                    message = buffer[:match_end]
                    self.remaining_data = buffer[match_end:]
                    return message
                
                if len(buffer) > 10000:
                    print("Warning: Buffer too large, processing as is")
                    self.remaining_data = ""
                    return buffer
                
                time.sleep(0.1)
                
            except Exception as e:
                print(f"Error receiving data: {e}")
                self.connected = False
                return buffer if buffer else None
    
    def send_answer(self, teleword):
        try:
            self.socket.sendall((teleword + '\n').encode('utf-8'))
            return True
        except Exception as e:
            print(f"Error sending answer: {e}")
            self.connected = False
            return False
    
    def parse_puzzle(self, data):
        try:
            info_match = re.search(r'Puzzle (\d+) \((\d+)x(\d+)\)', data)
            if not info_match:
                print("Could not find puzzle info")
                return None
            
            puzzle_number = int(info_match.group(1))
            rows = int(info_match.group(2))
            cols = int(info_match.group(3))
            info = info_match.group(0)
            
            grid_letters = []
            grid_section = data.split("Grid:")[1].split("Words to find:")[0].strip()
            grid_lines = [line.strip() for line in grid_section.split("\n") if line.strip()]
            
            for line in grid_lines:
                if line.startswith("|") and line.endswith("|"):
                    letters = line[1:-1].replace(" ", "")
                    grid_letters.extend(list(letters))
            
            words_section = data.split("Words to find:")[1].split("Enter Teleword:")[0].strip()
            words = []
            
            for line in words_section.split('\n'):
                if '=' in line or not line.strip():  
                    continue
                line_words = re.findall(r'\b[A-Z]+\b', line.upper())
                words.extend(line_words)
            
            # Save to file for solver
            self.save_to_file(grid_letters, words)
            
            return {
                "puzzle_number": puzzle_number,
                "total_puzzles": 0, 
                "info": info,
                "dimensions": [rows, cols],
                "grid_letters": grid_letters,
                "words": words
            }
            
        except Exception as e:
            print(f"Error parsing puzzle: {e}")
            import traceback
            traceback.print_exc()
            return None
    
    def save_to_file(self, grid_letters, words):
        try:
            with open("teleword.txt", "w") as file:
                file.write(','.join(grid_letters) + '\n\n')
                file.write(','.join(words))
            print("Puzzle data saved to teleword.txt")
            return True
        except Exception as e:
            print(f"Error saving to file: {e}")
            return False
    
    def solve_teleword(self):
        import subprocess
        try:
            result = subprocess.run(["./solver.exe", "teleword.txt"], capture_output=True, text=True)
            teleword = result.stdout.strip()
            print(f"Solver returned teleword: {teleword}")
            return teleword
        except Exception as e:
            print(f"Error running solver: {e}")
            return input("Failed to solve automatically. Please enter teleword manually: ")
    
    def play(self):
        if not self.connect():
            return
        
        try:
            while self.connected:
                data = self.receive_complete_message()
                if not data:
                    break
                
                print("\nReceived data from server:")
                print(data)
                
                if "Enter Teleword:" in data:
                    puzzle_data = self.parse_puzzle(data)
                    if puzzle_data:
                        print("\nSolving puzzle...")
                        teleword = self.solve_teleword()
                        print(f"Sending teleword: {teleword}")
                        self.send_answer(teleword)
                
                elif "Congratulations!" in data:
                    print("\nGame completed!")
                    print("\n" + "=" * 60)
                    print("=" * 60)
                    flag_match = re.search(r'flag\{.*?\}', data)
                    if flag_match:
                        print(f"Flag: {flag_match.group(0)}")
                    break
                
                time.sleep(0.2)
        
        except KeyboardInterrupt:
            print("\nExiting...")
        except Exception as e:
            print(f"Error: {e}")
            import traceback
            traceback.print_exc()
        finally:
            if self.socket:
                self.socket.close()


if __name__ == "__main__":
    host =  '143.110.186.64'
    port = 32768
    
    
    client = PuzzleClient(host, port)
    client.play()