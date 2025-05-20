const Joi = require("joi")
const prisma = require("../helpers/database")
const validate = require("../helpers/validation")


class _soilData {
    GetValue = async (id) => {
        try {
            const detail = await prisma.data_soil.findFirst({
                where: {
                    id: id,
                },
                select: {
                    value: true,                    
                }
            })

            return {
                status: true,
                data: detail,
            }

        } catch (error) {
            console.error('GetValue soilData module Error: ', error);
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
                value: Joi.number().required(),
            }).options({ abortEarly: false });

            validate(schema, body);

            const sen = await prisma.data_soil.findFirst({
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
                    error: 'Id Not Found'
                }
            }

            const update = await prisma.data_soil.updateMany({
                where: {
                    id: body.id
                },
                data: {
                    value: body.value,                    
                }
            })
            return {
                status: true,
                data: update,
            };

        } catch (error) {
            console.error('sendData soilData module Error: ', error);
            return {
                status: false,
                error,
            }
        }
    }
}

module.exports = new _soilData();