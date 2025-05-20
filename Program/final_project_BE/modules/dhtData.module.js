const Joi = require("joi")
const prisma = require("../helpers/database")
const validate = require("../helpers/validation")

class _dhtData {
    GetValue = async (id) => {
        try {
            const detail = await prisma.data_sht.findFirst({
                where: {
                    id: id,
                },
                select: {
                    kelembapan: true,
                    suhu: true
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
                kelembapan: Joi.number().required(),
                suhu: Joi.number().required()
            }).options({ abortEarly: false });

            validate(schema, body);

            const sen = await prisma.data_sht.findFirst({
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

            const update = await prisma.data_sht.updateMany({
                where: {
                    id: body.id
                },
                data: {
                    kelembapan: body.kelembapan,
                    suhu: body.suhu
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

module.exports = new _dhtData();