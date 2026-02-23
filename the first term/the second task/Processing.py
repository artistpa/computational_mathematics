import matplotlib.pyplot as plt
import numpy as np

# Чтение данных из файлов
x_data = []
y_data = []

try:
    # Чтение x координат
    with open('x.csv', 'r') as f:
        for line in f:
            x_data.append(float(line.strip()))

    # Чтение y координат
    with open('y.csv', 'r') as f:
        for line in f:
            y_data.append(float(line.strip()))

    print(f"Прочитано {len(x_data)} точек для x и {len(y_data)} точек для y")

    # Построение графика
    plt.figure(figsize=(12, 8))
    plt.plot(x_data, y_data, 'b-', linewidth=1, alpha=0.7)
    plt.scatter(x_data[0], y_data[0], color='green', s=100, label='Начальная точка', zorder=5)
    plt.scatter(x_data[-1], y_data[-1], color='red', s=100, label='Конечная точка', zorder=5)

    plt.xlabel('x', fontsize=12)
    plt.ylabel('y', fontsize=12)
    plt.title('Траектория y(x) в задаче трех тел', fontsize=14)
    plt.grid(True, alpha=0.3)
    plt.legend()
    plt.axis('equal')  # Сохраняем пропорции осей

    # Добавляем информацию о параметрах
    plt.text(0.02, 0.98, f'Количество точек: {len(x_data)}',
             transform=plt.gca().transAxes, verticalalignment='top')

    plt.tight_layout()
    plt.show()

    # Дополнительный график: траектория с цветовой кодировкой по времени
    plt.figure(figsize=(12, 8))

    # Создаем цветовую карту по времени
    colors = np.arange(len(x_data))

    scatter = plt.scatter(x_data, y_data, c=colors, cmap='viridis', s=5, alpha=0.7)
    plt.colorbar(scatter, label='Шаг итерации')

    plt.scatter(x_data[0], y_data[0], color='green', s=150, label='Начало', zorder=5, marker='o')
    plt.scatter(x_data[-1], y_data[-1], color='red', s=150, label='Конец', zorder=5, marker='s')

    plt.xlabel('x', fontsize=12)
    plt.ylabel('y', fontsize=12)
    plt.title('Траектория y(x) с цветовой кодировкой по времени', fontsize=14)
    plt.grid(True, alpha=0.3)
    plt.legend()
    plt.axis('equal')

    plt.tight_layout()
    plt.show()

except FileNotFoundError as e:
    print(f"Ошибка: Файл не найден: {e}")
    print("Сначала запустите C++ программу, чтобы создать файлы x.csv и y.csv")
except Exception as e:
    print(f"Произошла ошибка: {e}")