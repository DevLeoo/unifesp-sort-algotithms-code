import fs from "fs";
import csv from "csv-parser";

export class QuickSort {
  data: Array<number> = undefined!;

  public async sort() {
    const start: any = new Date();
    console.log("Start: ", start);

    const sorted = this.main(this.data);

    const end: any = new Date();
    console.log("End: ", end);
    console.log("Diff (miliseconds): ", end - start);

    console.log(sorted);
  }

  async loadData() {
    const data = await readCSVFile("./cenarios/1000.csv");

    this.setData(data);
  }

  setData(data: number[]) {
    this.data = data;
  }

  main(data: number[]): any {
    if (data.length <= 1) {
      return data;
    }

    const pivot = data[0];
    const left = [];
    const right = [];

    for (let i = 1; i < data.length; i++) {
      if (data[i] < pivot) {
        left.push(data[i]);
      } else {
        right.push(data[i]);
      }
    }

    return [...this.main(left), pivot, ...this.main(right)];
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
    const instance = new QuickSort();
    await instance.loadData();
    await instance.sort();
  } catch (e) {
    console.log(e);
  }
})();
