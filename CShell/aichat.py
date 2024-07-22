import subprocess
from openai import OpenAI
import markdown
from rich.console import Console
from rich.markdown import Markdown
import datetime
import os
import tempfile
import sys

console = Console()

client = OpenAI(
    api_key='FILL-IT-HERE_WHATEVER-U-GOT')


def create_temp_file(code, extension):
    with tempfile.NamedTemporaryFile(mode='w', suffix=f'.{extension}', delete=False) as temp:
        temp.write(code)
    return temp.name


def execute_code_snippet(code, language):
    try:
        if language == 'python':
            temp_file = create_temp_file(code, 'py')
            result = subprocess.run(
                [sys.executable, temp_file], capture_output=True, text=True)
        elif language == 'javascript':
            temp_file = create_temp_file(code, 'js')
            result = subprocess.run(
                ['node', temp_file], capture_output=True, text=True)
        elif language == 'bash':
            temp_file = create_temp_file(code, 'sh')
            result = subprocess.run(
                ['bash', temp_file], capture_output=True, text=True)
        else:
            return "Unsupported language"

        os.unlink(temp_file)  # Remove the temporary file

        if result.returncode == 0:
            return result.stdout
        else:
            return f"Error in code execution: {result.stderr}"
    except FileNotFoundError as e:
        return f"Error: Required interpreter not found. Details: {str(e)}"
    except Exception as e:
        return f"An unexpected error occurred: {str(e)}"


# System prompt for the AI
SYSTEM_PROMPT = """
You are an AI assistant capable of chatting with users and executing terminal commands upon request. Your capabilities include:
Answering user queries
Suggesting terminal commands to execute
Interpreting the output of executed commands
Providing troubleshooting steps for common issues
Offering recommendations for software and tools based on user needs
Explaining Linux commands and concepts in detail
Summarizing long texts or documents upon request
Guidelines:
When suggesting a command, format it as: [EXECUTE] command [/EXECUTE].
You can now execute multi-line code snippets in Python, JavaScript, and Bash.
To suggest a code snippet for execution, use the following format:
[CODE_EXECUTE:language]
code snippet here
[/CODE_EXECUTE]
Replace 'language' with 'python', 'javascript', or 'bash'.
Ensure the code is safe to execute and doesn't perform any harmful operations.Do not include comments in the code.
Provide a brief explanation of what the command does before suggesting it.
When reading files ,limit the output of file to max 10 lines.
After command execution, summarize the output for the user.
When providing troubleshooting steps, offer them in a clear, step-by-step format.
Reply in markdown format
When explaining commands or concepts, aim for clarity and include examples when possible.
Additional Instructions:
User cannot modify command that u give , so adjust it with proper path , parameter properly
Be proactive in suggesting useful tips and best practices related to Linux usage.
Ensure all terminal commands and explanations are compatible with Linux Zorin OS.
For security-related queries, prioritize safe practices and provide warnings about potential risks.
If a command requires elevated permissions, inform the user to use sudo responsibly.
Maintain extremely professional tone throughout the conversation.
Ensure you give only one EXECUTE in one chat and limit your reply as much as possible
"""

LOG_DIR = "chat_logs"


def chat_with_ai(messages):
    response = client.chat.completions.create(
        model="gpt-4o-mini",
        messages=messages
    )
    return response.choices[0].message.content


def execute_command(command):
    try:
        result = subprocess.run(command, shell=True,
                                check=True, capture_output=True, text=True)
        return result.stdout
    except subprocess.CalledProcessError as e:
        return f"Error executing command: {e}"


def log_conversation(user_input, ai_response, log_file):
    timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    with open(log_file, "a", encoding="utf-8") as f:
        f.write(f"\n[{timestamp}] User: {user_input}\n")
        f.write(f"[{timestamp}] AI: {ai_response}\n")


def main():
    messages = [{"role": "system", "content": SYSTEM_PROMPT}]

    console.print(
        "Welcome to AI Terminal Chat! Type 'exit' to quit.", style="bold green")

    os.makedirs(LOG_DIR, exist_ok=True)

    log_file = os.path.join(
        LOG_DIR, f"chat_log_{datetime.datetime.now().strftime('%Y%m%d_%H%M%S')}.txt")

    while True:
        user_input = console.input("[bold blue]You:[/bold blue] ")
        if user_input.lower() == 'exit':
            break

        messages.append({"role": "user", "content": user_input})
        ai_response = chat_with_ai(messages)

        log_conversation(user_input, ai_response, log_file)

        console.print(Markdown(f"# AI:\n\n{ai_response}"))

        if "[CODE_EXECUTE:" in ai_response and "[/CODE_EXECUTE]" in ai_response:
            start = ai_response.index("[CODE_EXECUTE:") + 14
            language_end = ai_response.index("]", start)
            language = ai_response[start:language_end].strip().lower()
            code_start = language_end + 1
            code_end = ai_response.index("[/CODE_EXECUTE]")
            code = ai_response[code_start:code_end].strip()

            user_permission = console.input(
                f"[bold yellow]AI wants to execute {language} code. Allow? (y/n):[/bold yellow] ")

            if user_permission.lower() == 'y':
                output = execute_code_snippet(code, language)
                console.print("[bold cyan]Code Execution Output:[/bold cyan]")
                console.print(output)
                messages.append(
                    {"role": "system", "content": f"Code execution output: {output}"}
                )
                summary = chat_with_ai(messages)
                console.print(
                    Markdown(f"[bold green]AI summary:[/bold green]\n\n{summary}"))

                log_conversation(
                    f"[CODE_EXECUTE:{language}] {code}", output, log_file)
                log_conversation("AI summary", summary, log_file)
            else:
                console.print("Code execution denied.", style="bold red")
                log_conversation(
                    f"[CODE_EXECUTE:{language} DENIED]", code, log_file)

        elif "[EXECUTE]" in ai_response and "[/EXECUTE]" in ai_response:
            start = ai_response.index("[EXECUTE]") + 9
            end = ai_response.index("[/EXECUTE]")
            command = ai_response[start:end].strip()

            user_permission = console.input(
                f"[bold yellow]AI wants to execute:[/bold yellow] {command}\n[bold yellow]Allow? (y/n):[/bold yellow] ")

            if user_permission.lower() == 'y':
                output = execute_command(command)
                console.print(
                    "[bold cyan]Command Execution Output:[/bold cyan]")
                console.print(output)
                messages.append(
                    {"role": "system", "content": f"Command output: {output}"}
                )
                summary = chat_with_ai(messages)
                console.print(
                    Markdown(f"[bold green]AI summary:[/bold green]\n\n{summary}"))

                log_conversation(f"[EXECUTE] {command}", output, log_file)
                log_conversation("AI summary", summary, log_file)
            else:
                console.print("Command execution denied.", style="bold red")
                log_conversation("[EXECUTE DENIED]", command, log_file)

        messages.append({"role": "assistant", "content": ai_response})

    console.print(
        f"Chat session ended. Log file saved to: {log_file}", style="bold green")


if __name__ == "__main__":
    main()