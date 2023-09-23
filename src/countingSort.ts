import fs from "fs";
import csv from "csv-parser";

export class CountingSort {
  data: Array<number> = undefined!;

  constructor() {
    this.loadData();
  }

  public sort() {
    const start: any = new Date();
    console.log("Start: ", start);

    const sorted = this.main(this.data);

    const end: any = new Date();
    console.log("End: ", end);
    console.log("Diff (miliseconds): ", end - start);

    //console.log(sorted);
  }

  async loadData() {
    const data = await readCSVFile("./cenarios/1000000qo.csv");
    this.setData(data);
  }

  setData(data: number[]) {
    this.data = data;
  }

  main(data: number[]): any {
    const max = Math.max(...data);

    const count = new Array(max + 1).fill(0);

    for (let i = 0; i < data.length; i++) {
      count[data[i]]++;
    }

    const sortedArr = [];
    for (let i = 0; i <= max; i++) {
      while (count[i] > 0) {
        sortedArr.push(i);
        count[i]--;
      }
    }

    return sortedArr;
  }
}

async function readCSVFile(filePath: string): Promise<number[]> {
  const results: number[] = [];

  return new Promise((resolve, reject) => {
    fs.createReadStream(filePath)
      .pipe(csv())
      .on("data", (data) => results.push(Number(data["0"])))
      .on("end", () => resolve(results))
      .on("error", (error) => reject(error));
  });
}

(async () => {
  try {
    const instance = new CountingSort();
    await instance.loadData();
    await instance.sort();
  } catch (e) {
    console.log(e);
  }
})();
