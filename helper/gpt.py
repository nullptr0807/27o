import os
import requests
import base64
import json

# Configuration
GPT4V_ENDPOINT = "https://openaiajin.openai.azure.com/openai/deployments/GPT4/chat/completions?api-version=2024-02-15-preview"
GPT4V_KEY = "*"
#IMAGE_PATH = "YOUR_IMAGE_PATH"
#encoded_image = base64.b64encode(open(IMAGE_PATH, 'rb').read()).decode('ascii')

headers = {
    "Content-Type": "application/json",
    "api-key": GPT4V_KEY,
}

# Payload for the request
temperature = 0.9
top_p = 0.8
max_tokens = 3000
payload = {
  "messages": [
    {
      "role": "system",
      "content": [
        {
          "type": "text",
          "text": "You are an AI assistant that helps people find information."
        }
      ]
    }
  ],
  "temperature": temperature,
  "top_p": top_p,
  "max_tokens": max_tokens
}

def send_message(payload):
    try:
        response = requests.post(GPT4V_ENDPOINT, headers=headers, json=payload)
        response.raise_for_status()  # Will raise an HTTP Error if the HTTP request returned an unsuccessful status code
        response_data = response.json()
        # print(response_data)
        text = response_data['choices'][0]['message']['content'].strip()

        message_from_gpt =    {
            "role": "assistant",
            "content": [
            {
              "type": "text",
              "text": text
            }
          ]
        }

        payload["messages"].append(message_from_gpt)
        return text
    
    except requests.RequestException as e:
        raise SystemExit(f"Failed to make the request. Error: {e}")

print(f"Temperature: {temperature}, Top P: {top_p}, Max Tokens: {max_tokens}")

while True:  
    # input and command parse
    user_input = input("You: ")  
    if user_input.lower() == "exit":  
        break  
    if user_input.lower() == "clear":
        payload["messages"] = []
        print("[Chat history has been cleared]\n\n")
        continue
    if user_input.lower() == "save":
      with open('chat_history.json', 'a') as outfile:
        json.dump(payload, outfile)
        outfile.write('\n')
      print("[Chat history has been saved]\n\n")
      continue
    if user_input.lower() == "show":
        print(json.dumps(payload, indent=4))
      
    # Update the history with the user's input
    user_message = {
        "role": "user",
        "content": [
            {
                "type": "text",
                "text": user_input
            }
        ]
    }  
    payload["messages"].append(user_message)
      
    text_from_gpt = send_message(payload)  
    print(f"GPT-4: {text_from_gpt}" + "\n")  
    

