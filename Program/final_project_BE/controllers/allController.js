const { Router } = require("express")
const m$allSensor = require("../modules/allSensor.module")
const response = require("../helpers/response")

const allController = Router()

/** Update atau kirim data
* 
* https:localhost:8000/api/
{
"id": 0
"soil_hum": true,
"dht_hum": true,
"dht_temp": true
}
*
**/
allController.put("/sendvalue", async (req, res) => {
    const add = await m$allSensor.sendData(req.body)
    response.sendResponse(res, add)
})

/** Get Data
 * 
 * 
 */

allController.get("/getdata/:id", async (req, res) => {
    const get = await m$allSensor.GetValue(Number(req.params.id))
    response.sendResponse(res, get)
})

module.exports = allController;