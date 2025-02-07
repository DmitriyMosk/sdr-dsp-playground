import numpy as np
import matplotlib.pyplot as plt

# Параметры сигнала
fs = 10240  # Частота дискретизации (Гц)
N = 1024    # Количество отсчетов
f0 = 1000   # Исходная частота сигнала (Гц)
df = 2*f0     # Частотный сдвиг (Гц), хотим удвоить частоту

# Временная ось
n = np.arange(N)
t = n / fs  # Время в секундах

# Исходный сигнал (косинус)
x = np.cos(2 * np.pi * f0 * t)

# --- 1. Дискретное преобразование Фурье (ДПФ) ---
X = np.fft.fft(x)
freqs = np.fft.fftfreq(N, 1/fs)  # Ось частот

# --- 2. Преобразование Гильберта в частотной области ---
H = np.zeros(N)  # Фильтр Гильберта
H[0] = 1  # DC-компонент остаётся неизменной
H[1:N//2] = 2  # Удвоение амплитуды для положительных частот
H[N//2] = 1  # Nyquist частота остаётся неизменной (если N чётное)
H[N//2+1:] = 0  # Отрицательные частоты убираем

Z = X * H  # Применяем Гильберт в частотной области
# Z = X 

# --- 3. Сдвиг спектра на df ---
k_shift = int(df * N / fs)  # Сдвиг в отсчётах
Z_shifted = np.roll(Z, k_shift)  # Циклический сдвиг спектра

# --- 4. Обратное ДПФ (iFFT) ---
y_complex = np.fft.ifft(Z_shifted)  # Восстанавливаем временной сигнал
y_real = np.real(y_complex)  # Берём вещественную часть

# --- 5. Визуализация ---
plt.figure(figsize=(12, 8))

# Исходный сигнал
plt.subplot(3, 1, 1)
plt.plot(t[:100], x[:100], label="Исходный сигнал x[n]")
plt.xlabel("Время (с)")
plt.ylabel("Амплитуда")
plt.legend()
plt.grid()

# Спектр исходного сигнала
plt.subplot(3, 1, 2)
plt.plot(freqs[:N//2], np.abs(X[:N//2]), label="Спектр X[k] (до обработки)", linestyle="--")
plt.plot(freqs[:N//2], np.abs(Z_shifted[:N//2]), label="Спектр Z[k] (сдвинутый)", color='r')
plt.xlabel("Частота (Гц)")
plt.ylabel("Амплитуда")
plt.legend()
plt.grid()

# Исправленный сигнал
plt.subplot(3, 1, 3)
plt.plot(t[:100], y_real[:100], label="Исправленный сигнал y[n] (c Гильбертом и сдвигом)", color='g')
plt.xlabel("Время (с)")
plt.ylabel("Амплитуда")
plt.legend()
plt.grid()

plt.tight_layout()
plt.show()
