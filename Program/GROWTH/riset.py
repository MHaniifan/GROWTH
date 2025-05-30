import serial
import requests
import re

# Konfigurasi RFC2217 (Wokwi)
ser = serial.serial_for_url(
    "rfc2217://localhost:4000",  # Port sesuai setting Wokwi (biasanya 8000)
    baudrate=9600,
    timeout=1,
)

api_url = "http://192.168.65.163:3000/api/all/sendvalue"  # Ganti dengan URL API


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


while True:
    try:
        # Baca data dari Serial
        line = ser.readline().decode("utf-8").strip()
        print("Data mentah:", line)

        if line:  # Hanya proses jika ada data
            sensor_data = parse_sensor_data(line)

            if sensor_data:
                # Kirim ke API
                response = requests.post(
                    api_url,
                    json={
                        "id": 1,
                        "soil_hum": sensor_data["soil"],
                        "dht_hum": sensor_data["humidity"],
                        "dht_temp": sensor_data["temperature"],
                        "fan_stat": sensor_data["fan"],
                        "pump_stat": sensor_data["pump"],
                        "fan_hour": 12,
                        "pump_hour": 10,
                    },
                )
                print("Status API:", response.status_code)
                print("Data terkirim:", sensor_data)
            else:
                print("Gagal parsing data")

    except Exception as e:
        print("Error:", str(e))
        try:
            ser.close()
        except:
            pass
        ser = serial.serial_for_url("rfc2217://localhost:8000", baudrate=9600)
