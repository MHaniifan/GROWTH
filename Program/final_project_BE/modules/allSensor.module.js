const Joi = require("joi")
const prisma = require("../helpers/database")
const validate = require("../helpers/validation")

class _allSensor {
    GetValue = async (id) => {
        try {
            const detail = await prisma.all_sensor.findFirst({
                where: {
                    id: id,
                },
                select: {
                    soil_hum: true,
                    dht_hum: true,
                    dht_temp: true
                }
            })

            return {
                status: true,
                data: detail,
            }

        } catch (error) {
            console.error('GetValue dataCurrentSht module Error: ', error);
            return {
                status: false,
                error,
            }
        }
    };

    // Update Data
    sendData = async (body) => {
        try {
            const schema = Joi.object({
                id: Joi.number().required(),
                soil_hum: Joi.number().required(),
                dht_hum: Joi.number().required(),
                dht_temp: Joi.number().required()
            }).options({ abortEarly: false });

            validate(schema, body);

            const sen = await prisma.all_sensor.findFirst({
                where: {
                    id: body.id
                },
                select: {
                    id: true
                } 
            })

            if (!sen) {
                return {
                    status: false,
                    code: 401,
                    error: 'Id_Sensor Not Found'
                }
            }

            const update = await prisma.all_sensor.updateMany({
                where: {
                    id: body.id
                },
                data: {
                    soil_hum: body.soil_hum,
                    dht_hum: body.dht_hum,
                    dht_temp: body.dht_temp
                }
            })
            return {
                status: true,
                data: update,
            };

        } catch (error) {
            console.error('sendData dataCurrentDht module Error: ', error);
            return {
                status: false,
                error,
            }
        }
    }
}

module.exports = new _allSensor();