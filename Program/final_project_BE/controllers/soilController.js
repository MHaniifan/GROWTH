const { Router } = require("express")
const m$Nowsoil = require("../modules/soilData.module")
const response = require("../helpers/response")

const soilController = Router()

/** Update atau kirim data
* 
* https:localhost:8000/api/
{
"id": 0
"value":
}
*
**/
soilController.put("/soil/sendvalue", async (req, res) => {
    const add = await m$Nowsoil.sendData(req.body)
    response.sendResponse(res, add)
})

/** Get Data
 * 
 * 
 */

soilController.get("/getdata/:id", async (req, res) => {
    const get = await m$Nowsoil.GetValue(Number(req.params.id))
    response.sendResponse(res, get)
})

module.exports = soilController;