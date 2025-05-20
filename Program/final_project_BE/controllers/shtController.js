const { Router } = require("express")
const m$Nowdht = require("../modules/dhtData.module")
const response = require("../helpers/response")

const shtController = Router()

/** Update atau kirim data
* 
* https:localhost:8000/api/
{
"id": 0
"kelembapan":
"suhu": 
}
*
**/
shtController.put("/sendvalue", async (req, res) => {
    const add = await m$Nowdht.sendData(req.body)
    response.sendResponse(res, add)
})

/** Get Data
 * 
 * 
 */

shtController.get("/getdata/:id", async (req, res) => {
    const get = await m$Nowdht.GetValue(Number(req.params.id))
    response.sendResponse(res, get)
})

module.exports = shtController;