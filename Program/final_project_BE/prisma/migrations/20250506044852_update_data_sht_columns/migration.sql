/*
  Warnings:

  - You are about to drop the column `value` on the `data_sht` table. All the data in the column will be lost.
  - Added the required column `kelembapan` to the `data_sht` table without a default value. This is not possible if the table is not empty.
  - Added the required column `suhu` to the `data_sht` table without a default value. This is not possible if the table is not empty.

*/
-- AlterTable
ALTER TABLE `data_sht` DROP COLUMN `value`,
    ADD COLUMN `kelembapan` DOUBLE NOT NULL,
    ADD COLUMN `suhu` DOUBLE NOT NULL;
