import re
import matplotlib.pyplot as plt

def read_pie_chart_file(file_path):
    data = {}
    
    with open(file_path, 'r', encoding='utf-8') as file:
        lines = file.readlines()
    
    for line in lines:
        if line.startswith("Pie Chart") or line.startswith("=========="):
            continue
        
        match = re.match(r"(.+?)\s+-\s+([0-9.]+)% \((\d+)\)", line.strip())
        if match:
            category = match.group(1).strip()  
            percentage = float(match.group(2))  
            count = int(match.group(3))
            data[category] = (percentage, count)
    
    return data

def generate_pie_chart(data, title="Pie Chart"):
    categories = list(data.keys())
    percentages = [item[0] for item in data.values()]
    
    plt.figure(figsize=(20, 18)) 
    plt.pie(
        percentages,
        labels=categories,
        autopct='%1.1f%%',
        startangle=140,
        textprops={'fontsize': 15}  
    )
    plt.title(title, pad=30) 
    plt.show()

def read_bar_chart_file(file_path):
    data = {}
    
    with open(file_path, 'r', encoding='utf-8') as file:
        lines = file.readlines()
    
    for line in lines:
        if line.startswith("Bar Chart") or line.startswith("=========="):
            continue
        
        match = re.match(r"(.+?)\s+\|\s+(#*) \((\d+)\)", line.strip())
        if match:
            category = match.group(1).strip() 
            bar_length = len(match.group(2)) 
            count = int(match.group(3)) 
            data[category] = (bar_length, count)
    
    return data

def generate_bar_chart(data, title="Bar Chart"):
    categories = list(data.keys())
    counts = [item[1] for item in data.values()]
    
    plt.figure(figsize=(10, 8))
    bars = plt.barh(categories, counts, color='skyblue')
    
    for bar, count in zip(bars, counts):
        plt.text(
            bar.get_width() + 1,
            bar.get_y() + bar.get_height() / 2,
            str(count),  
            va='center',  
            fontsize=10 
        )
    
    plt.xlabel('Quantidade')
    plt.title(title)
    plt.show()


pie_chart_file_path_1 = 'Main/piechartProfessions.txt'
pie_chart_file_path_2 = 'Main/piechartReligions.txt' 
pie_chart_file_path_3 = 'Main/piechartEducations.txt' 
bar_chart_file_path_1 = 'Main/barchart.txt'
bar_chart_file_path_2 = 'Main/barchartFutebolistasPorDecada.txt'
bar_chart_file_path_3 = 'Main/barchartPoliticosPorDecada.txt'

pie_data_1 = read_pie_chart_file(pie_chart_file_path_1)
pie_data_2 = read_pie_chart_file(pie_chart_file_path_2)
pie_data_3 = read_pie_chart_file(pie_chart_file_path_3)
bar_data_1 = read_bar_chart_file(bar_chart_file_path_1)
bar_data_2 = read_bar_chart_file(bar_chart_file_path_2)
bar_data_3 = read_bar_chart_file(bar_chart_file_path_3)

generate_bar_chart(bar_data_1, title="Proporção de Gêneros")
generate_bar_chart(bar_data_2, title="Proporção de Futebolistas por década")
generate_bar_chart(bar_data_3, title="Proporção de Políticos por década")
generate_pie_chart(pie_data_1, title="Proporção de Profissões")
generate_pie_chart(pie_data_2, title="Proporção de Religiões")
generate_pie_chart(pie_data_3, title="Proporção de Escolas")
