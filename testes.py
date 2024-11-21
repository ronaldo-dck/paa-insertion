import pandas as pd
import os
import subprocess
import time
from tqdm import tqdm

paths = [
    "./datasets/Aleatórios",
    "./datasets/Decrescentes",
    "./datasets/Ordenados",
    "./datasets/ParcialmenteOrdenados",
]

file_lists = [[] for _ in range(4)]


for i, path in enumerate(paths):
    if os.path.exists(path):
        for root, _, files in os.walk(path):
            for file in files:
                file_lists[i].append(os.path.join(root, file))
    else:
        print(f"O caminho {path} não existe!")

for file_list in file_lists:
    file_list.sort(key=lambda x: int(''.join(filter(str.isdigit, x))))

lists_args = [['I'],
              ['B', '10'],
              ['B', '100'],
              ['B', '1000'],
              ]

with open('logs/tempos.csv','w') as f:
    f.write('I;time;file;args')

for idx, file_list in enumerate(file_lists):
    for file in tqdm(file_list, desc=f"{paths[idx]}", leave=False):
        # print(file)
        for args in lists_args:
            for inter in range(6):
                command = ['./insertion.x'] + [file] + args
                # print(command)
                start_time = time.time()
                result = subprocess.run(
                    command, capture_output=True, text=True, check=True)
                end_time = time.time()
                execution_time = end_time - start_time
                linha_resultado = f'{inter};{execution_time:.4f};{file};{args}\n'
                with open('logs/tempos.csv','a+') as f:
                    f.write(linha_resultado)