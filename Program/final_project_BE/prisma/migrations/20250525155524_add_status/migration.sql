/*
  Warnings:

  - You are about to drop the column `fun_hour` on the `all_sensor` table. All the data in the column will be lost.
  - Added the required column `fan_hour` to the `all_sensor` table without a default value. This is not possible if the table is not empty.
  - Added the required column `fan_stat` to the `all_sensor` table without a default value. This is not possible if the table is not empty.
  - Added the required column `pump_stat` to the `all_sensor` table without a default value. This is not possible if the table is not empty.

*/
-- AlterTable
ALTER TABLE `all_sensor` DROP COLUMN `fun_hour`,
    ADD COLUMN `fan_hour` DOUBLE NOT NULL,
    ADD COLUMN `fan_stat` INTEGER NOT NULL,
    ADD COLUMN `pump_stat` INTEGER NOT NULL;
