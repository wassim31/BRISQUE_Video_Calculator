import pandas as pd
import matplotlib.pyplot as plt

file_path = 'result.csv'  
data = pd.read_csv(file_path)

frames = data['frame']
brisk_values = data['brisque']

plt.figure(figsize=(10, 6))
plt.plot(frames, brisk_values, color='blue', marker='o', linestyle='-', markersize=5)

plt.title('Brisk Values per Frame')
plt.xlabel('frame')
plt.ylabel('brisque')

plt.xlim(1, 1000)  
plt.ylim(0, 100)   

plt.grid(True)

plt.show()
