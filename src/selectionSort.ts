import fs from "fs";
import csv from "csv-parser";

export class SelectionSort {
  data: Array<number> = undefined!;

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
    const n = data.length;

    for (let i = 0; i < n - 1; i++) {
      let minIndex = i;

      for (let j = i + 1; j < n; j++) {
        if (data[j] < data[minIndex]) {
          minIndex = j;
        }
      }

      if (minIndex !== i) {
        const temp = data[i];
        data[i] = data[minIndex];
        data[minIndex] = temp;
      }
    }

    return data;
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
    const instance = new SelectionSort();
    await instance.loadData();
    await instance.sort();
  } catch (e) {
    console.log(e);
  }
})();
