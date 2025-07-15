import subprocess

command  = ['ping', '-c' ,'2', 'clccg.mcpro.io']
result = subprocess.run(command, capture_output=True, text=True)
output = result.stdout.strip()

print("Command Output:")
print(output)
