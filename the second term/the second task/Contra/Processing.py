import numpy as np
import matplotlib.pyplot as plt

x = []
y = []
u = []

with open('x.txt', 'r') as f:
    for line in f:
        x.append(float(line.strip()))
with open('y.txt', 'r') as f:
    for line in f:
        y.append(float(line.strip()))
with open('u.txt', 'r') as f:
    for line in f:
        u.append(float(line.strip()))

x = np.array(x)
y = np.array(y)
u = np.array(u)
u = u.reshape(int(len(u) / 1001), 1001)
print(len(u))

# Создаём график
fig, ax = plt.subplots(figsize=(8, 6))

# Отображаем двумерное распределение с помощью imshow
im = ax.imshow(u, interpolation='bilinear', cmap='RdYlBu',
               extent=[x.min(), x.max(), y.min(), y.max()])

# Добавляем метки и заголовок
plt.title('Двумерное распределение U(x,y)')
plt.xlabel('Ось X')
plt.ylabel('Ось Y')

# Добавляем цветную панель для отображения масштаба
plt.colorbar(im, label='U')

plt.show()
