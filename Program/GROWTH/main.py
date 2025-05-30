import serial
import requests
import re
import time  # Untuk delay saat reconnect

# Konfigurasi Port Serial (COM11)
SERIAL_PORT = "COM11"  # Ganti dengan port yang sesuai (Linux: '/dev/ttyUSB0', Mac: '/dev/tty.usbmodem*')
BAUD_RATE = 9600

# URL API
API_URL = "http://192.168.159.163:3000/api/all/sendvalue"

# Inisialisasi Serial
def init_serial():
    try:
        return serial.Serial(
            port=SERIAL_PORT,
            baudrate=BAUD_RATE,
            timeout=1
        )
    except serial.SerialException as e:
        print(f"Gagal membuka port {SERIAL_PORT}: {e}")
        return None

# Fungsi untuk parsing data sensor
def parse_sensor_data(line):
    pattern = r"Kelembaban Tanah = (.+), Kelembaban Udara = (\d+), Suhu = (\d+), Pump = (\d+), Fan = (\d+)"
    match = re.match(pattern, line)
    if match:
        return {
            "soil": match.group(1),
            "humidity": int(match.group(2)),
            "temperature": int(match.group(3)),
            "pump": int(match.group(4)),
            "fan": int(match.group(5)),
        }
    return None

# Main loop
def main():
    ser = init_serial()
    if not ser:
        print("Konektivitas serial tidak tersedia.")
        return

    while True:
        try:
            # Baca data dari Serial
            if ser.in_waiting > 0:
                line = ser.readline().decode("utf-8").strip()
                print("Data mentah:", line)

                if line:  # Hanya proses jika ada data
                    sensor_data = parse_sensor_data(line)

                    if sensor_data:
                        # Kirim ke API
                        response = requests.put(
                            API_URL,
                            json={
                                "id": 1,
                                "soil_hum": float(sensor_data["soil"]),
                                "dht_hum": int(sensor_data["humidity"]),
                                "dht_temp":int(sensor_data["temperature"]),
                                "fan_stat": int(sensor_data["fan"]),
                                "pump_stat": int(sensor_data["pump"]),
                                "fan_hour": 12,
                                "pump_hour": 10,
                            },
                        )
                        print("Status API:", response.status_code)
                        print("Data terkirim:", sensor_data)
                    else:
                        print("Gagal parsing data")
            time.sleep(0.1)  # Delay kecil untuk menghindari CPU overload

        except serial.SerialException as e:
            print("Error serial:", str(e))
            ser.close()
            print("Menunggu 5 detik sebelum reconnect...")
            time.sleep(5)
            ser = init_serial()
        except Exception as e:
            print("Error umum:", str(e))
            ser.close()
            print("Menunggu 5 detik sebelum reconnect...")
            time.sleep(5)
            ser = init_serial()

if __name__ == "__main__":
    main()