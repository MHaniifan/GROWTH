const shtController = require('./controllers/shtController')
const soilController = require('./controllers/soilController')
const allController = require('./controllers/allController')

const _routes = [
    ['sht', shtController],
    ['all', allController],
    ['soil', soilController]
]

const routes = (app) => {
    _routes.forEach(route => {
        const [url, controller] = route
        app.use(`/api/${url}`,controller)
    })
}

module.exports = routes