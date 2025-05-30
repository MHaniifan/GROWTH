-- CreateTable
CREATE TABLE `all_sensor` (
    `id` INTEGER NOT NULL AUTO_INCREMENT,
    `soil_hum` DOUBLE NOT NULL,
    `dht_hum` DOUBLE NOT NULL,
    `dht_temp` DOUBLE NOT NULL,
    `fun_hour` DOUBLE NOT NULL,
    `pump_hour` DOUBLE NOT NULL,

    PRIMARY KEY (`id`)
) DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
